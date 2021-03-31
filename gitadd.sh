#!/bin/sh

cd ~/run/media/vibhanshu/New Volume/Academic-Files && git add --force --all :/ && git commit -m 'Some news updates' && git push --recurse-submodules=on-demand --set-upstream origin master --force 
# && git reflog expire --all --expire=now && git gc --prune=now --aggressive
