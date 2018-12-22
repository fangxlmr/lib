#  Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.


CC=gcc
C_INCLUDE_PATH=./include:./common
export C_INCLUDE_PATH
SRCS_PATH=./adt
#COMMON_PATH=./common

vpath %.h ./include ./common
vpath %c ./adt ./common ./tests

OBJS=vector.o stack.o queue.o bstree.o avl-tree.o \
	 binary-minheap.o hashtable.o dict.o \
	 comparator.o
test: test.o $(OBJS)
	$(CC) -o ./build/$@ $^ -lm
	mv *o ./build/

vector.o: vector.h
stack.o: stack.h
queue.o: queue.h
binary-minheap.o: binary-minheap.h comparator.h
comparator.o: comparator.h
avl-tree.o: avl-tree.h comparator.h
bstree.o: bstree.h comparator.h
hashtable.o: hashtable.h dict.h comparator.h
dict.o: dict.h comparator.h

.PHONY: clean
clean:
	rm -rf *.o ./build/*.o ./build/test