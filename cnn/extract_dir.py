# -*- coding: utf-8 -*-

import numpy as np
import sys
import os
from os import path

# change to your caffe root dir path
caffe_root = '/home/qtlab/pure_caffe/'
sys.path.insert(0, caffe_root + 'python')

import caffe

caffe.set_mode_gpu()
        
net = caffe.Net('conv_model/conv.prototxt',
                        # '/home/qtlab/Downloads/ran_all_vgg_finetune_0.0001_iter_44000.caffemodel',
                        'conv_model/conv_model.caffemodel',
                        caffe.TEST)

transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
transformer.set_transpose('data', (2,0,1))
transformer.set_mean('data', np.load(caffe_root + 'python/caffe/imagenet/ilsvrc_2012_mean.npy').mean(1).mean(1)) # mean pixel
transformer.set_raw_scale('data', 255)  # the reference model operates on images in [0,255] range instead of [0,1]
transformer.set_channel_swap('data', (2,1,0))  # the reference model has channels in BGR order instead of RGB

def get_mean(scores):
    (pc, pn, ph, pw) = scores.shape
    scores = np.reshape(scores, (pn, ph * pw))
    return scores.mean(axis=1)

def get_feature(img_file):
    
    net.blobs['data'].data[...] = transformer.preprocess('data', caffe.io.load_image(img_file))
    net.forward()
    scores = net.blobs['pool5'].data
    # scores = net.blobs['fc7'].data
    # return scores[0,]
    return get_mean(scores)

def extract_dir(dir_name):
    i = 0
    for parent,dirnames,filenames in os.walk(dir_name):
        for filename in filenames:
            if filename.endswith('.jpg') == False:
                continue
#            print path.join(parent,filename)
            img_filename = path.join(parent, filename)
            #try:
            feature = get_feature(img_filename)
            f = open(img_filename + '.alex', 'wb')
            f.write(feature.astype(np.float32))
            f.close()
            if i % 200 == 0:
                print i 
            i += 1
            #except:
            #    print img_filename
                

# perform feature extraction for the follwing directory
# extract_dir('/home/qtlab/dataset/ukbench/full')
extract_dir('/home/qtlab/dataset/Holidays')
