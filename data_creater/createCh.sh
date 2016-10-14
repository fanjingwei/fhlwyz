#!/bin/sh

foldName=$1

rm -r $foldName
rm -r picture
mkdir picture
mkdir $foldName

python create_mnist_image.py

mv rgb_t10k-images.idx3-ubyte rgb_t10k-images-idx3-ubyte
mv rgb_t10k-labels.idx1-ubyte rgb_t10k-labels-idx1-ubyte
mv rgb_train-images.idx3-ubyte rgb_train-images-idx3-ubyte
mv rgb_train-labels.idx1-ubyte rgb_train-labels-idx1-ubyte
mv t10k-images.idx3-ubyte t10k-images-idx3-ubyte
mv t10k-labels.idx1-ubyte t10k-labels-idx1-ubyte
mv train-images.idx3-ubyte train-images-idx3-ubyte
mv train-labels.idx1-ubyte train-labels-idx1-ubyte

gzip rgb_t10k-images-idx3-ubyte
gzip rgb_t10k-labels-idx1-ubyte
gzip rgb_train-images-idx3-ubyte
gzip rgb_train-labels-idx1-ubyte
gzip t10k-images-idx3-ubyte
gzip t10k-labels-idx1-ubyte
gzip train-images-idx3-ubyte
gzip train-labels-idx1-ubyte

mv picture $foldName/
mv rgb_t10k-images-idx3-ubyte.gz $foldName/
mv rgb_t10k-labels-idx1-ubyte.gz $foldName/
mv rgb_train-images-idx3-ubyte.gz $foldName/
mv rgb_train-labels-idx1-ubyte.gz $foldName/
mv t10k-images-idx3-ubyte.gz $foldName/
mv t10k-labels-idx1-ubyte.gz $foldName/
mv train-images-idx3-ubyte.gz $foldName/
mv train-labels-idx1-ubyte.gz $foldName/

