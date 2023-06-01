all: linked_list.o sort.o data.o dict1.o dict2.o dynamic_list.o dict1 dict2

dict1.o: ../dictionary_task/dict1.c data.h linked_list.h

dict2.o: ../dictionary_task/dict2.c data.h dynamic_list.h sort.h

sort.o: ../dictionary_task/data.h sort.h linked_list.h

linked_list.o: ../dictionary_task/linked_list.h

dynamic_list.o: ../dictionary_task/data.h

data.o: ../dictionary_task/linked_list.h

dict1:
	gcc -Wall -g -o dict1 dict1.o data.o linked_list.o

dict2:
	gcc -Wall -g -o dict2 dict2.o dynamic_list.o data.o sort.o




