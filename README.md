2012/12/02 Written by H. T.

This is convert program from matlab structure(libsvm, liblinear) to c structure.
	matlab --> c          (mat2libsvm, mat2liblinear)
	c          <-- matlab (only liblinear2mat. about libsvm, Sorry, not yet)
	
INSTALL:
At first, please type 'make' to compile.
make.m is MakeFile.

NOTE:I devloped this code with libsvm-3.14 and liblinear-1.92.

USAGE: libsvm
[label_vector, instance_matrix] = libsvmread('heart_scale.txt');
model=svmtrain(label_vector,instance_matrix);
model=train(label_vector,instance_matrix);
mat2libsvm(model, 'output_name'); <- convert matlab structure to c structure(libsvm structure)

Usage: liblinear
[label_vector, instance_matrix] = libsvmread('heart_scale.txt');
model=train(label_vector,instance_matrix);
mat2liblinear(model, 'output_name'); <- convert matlab structure to c structure(liblinear structure)