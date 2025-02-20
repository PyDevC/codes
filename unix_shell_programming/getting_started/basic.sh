!/usr/bin/env bash

#create single empty file
touch file
#create multiple empty files
touch file1 file2

# adding text to file
echo "Hello World" > file
# reading a file
cat file
# read two files  shows concatenated version
cat file file
# append to file
cat file >> file2

# copy files
cp file file2
# copy multiple files to a dir or another dir
cp file file file2

# remove a file
rm file
# ask before removing
rm -i file
# remove the directory recursively
rm -r dir

#move files or dir
mv file dir
mv file ~/file
# rename file
mv file file3 # as in same dir the file is renamed to file3

#list files and dir in current dir
ls
# list everything in current dir
ls -a
# list based on pattern
ls p* # all files starting with name p
# list inside a dir
ls dir

# establish symlink between two files
ln file ../file4

#change file or dir permissions
chmod +x file # makes file executable for everyone

#present working dir
pwd
# make a new dir
mkdir dir
# nested dir/file creation
mkdir -p dir1/dir2/ # will create dir1 then dir2 inside of dir1 

#remove dir
rmdir dir # opposite of mkdir

#change dir
ch dir
