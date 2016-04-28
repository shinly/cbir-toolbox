# -*- coding: utf-8 -*-

import numpy as np
import sys
import os
import skimage
from os import path

caffe_root = '/home/qtlab/pure_caffe/'
sys.path.insert(0, caffe_root + 'python')

import caffe

def get_mean(scores):
    (pc, pn, ph, pw) = scores.shape
    scores = np.reshape(scores, (pn, ph * pw))
    return scores.mean(axis=1)

def get_local(scores):
    (pc, pn, ph, pw) = scores.shape
    scores = np.reshape(scores, (pn * ph * pw))
    return (ph * pw, pn, scores)

def get_scores(img_file, layer_name, net, transformer):
    img = caffe.io.load_image(img_file)
    (h, w, c) = img.shape
    input_img = img
    if h != w:
        (mb, bh) = (h, True) if h > w else (w, False)
        input_img = skimage.img_as_float(np.zeros((mb, mb, 3)))
        if bh:
            input_img[:, :w, :] = img
        else:
            input_img[:h, :, :] = img

    net.blobs['data'].data[...] = transformer.preprocess('data', input_img)
    net.forward()
    scores = net.blobs[layer_name].data
    (pc, pn, ph, pw) = scores.shape
    if h != w:
        if h > w:
            scores = scores[:, :, :, :(pw*w/h)]
        else:
            scores = scores[:, :, :(ph*h/w), :]
    return scores

def get_feature(img_file, net, transformer):
    scores = get_scores(img_file, 'pool5', net, transformer)
    return get_mean(scores)

def extract_dir(dir_name, save_ext, net, transformer):
    i = 0
    for parent,dirnames,filenames in os.walk(dir_name):
        for filename in filenames:
            if filename.endswith('.jpg') == False:
                continue
#            print path.join(parent,filename)
            img_filename = path.join(parent, filename)
            try:
                feature = get_feature(img_filename, net, transformer)
                f = open(img_filename + save_ext, 'wb')
                f.write(feature.astype(np.float32))
                f.close()
                # (fn, fd, feature) = get_feature(img_filename)
                # f = open(img_filename + '.cnn_lp5', 'wb')
                # f.write(np.asarray([fn,fd],dtype=np.int32))
                # f.write(feature.astype(np.float32))
                # f.close()
                if i % 200 == 0:
                    print i

                i += 1
            except:
                print img_filename
                


if __name__ == '__main__':
    model_file = sys.argv[1]
    save_name = sys.argv[2]


    caffe.set_mode_gpu()
            
    net = caffe.Net('conv_model/conv.prototxt', 
        model_file, 
        caffe.TEST)

    transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
    transformer.set_transpose('data', (2,0,1))
    transformer.set_mean('data', np.load(caffe_root + 'python/caffe/imagenet/ilsvrc_2012_mean.npy').mean(1).mean(1)) # mean pixel
    transformer.set_raw_scale('data', 255)  # the reference model operates on images in [0,255] range instead of [0,1]
    transformer.set_channel_swap('data', (2,1,0))  # the reference model has channels in BGR order instead of RGB

    print save_name
    extract_dir('/home/qtlab/dataset/Holidays', save_name, net, transformer)

