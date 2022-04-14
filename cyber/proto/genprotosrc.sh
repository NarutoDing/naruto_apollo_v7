#!/bin/bash

#here is how to use protoc to generate proto files, this is not a standard approch, i will develop a standard way to do the next work, may be i will transfer it into
#cmakelist project or make a standard sh file, this file just depend on my system environment, and u will change it by yourself

#c++ protobuf
#modules audio
for i in `ls /home/naruto/naruto_apollo_v7/cyber/proto/*.proto`
do
/home/naruto/naruto_apollo/local_depends/protobuf-3.14.0/bin/protoc  -I/home/naruto/naruto_apollo_v7 --cpp_out=/home/naruto/naruto_apollo_v7/cyber/proto  $i
/home/naruto/naruto_apollo/local_depends/protobuf-3.14.0/bin/protoc  -I/home/naruto/naruto_apollo_v7 --python_out=/home/naruto/naruto_apollo_v7/cyber/proto  $i
echo $i
done


