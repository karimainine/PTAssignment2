##############################################################################
# COSC1283/1284 - Programming Techniques
# Semester 2 2011 Assignment #2
# Full Name        : Karim Mohamed Gamal Abulainine
# Student Number   : 3314713
# Yallara Username : s3314713@yallara.cs.rmit.edu.au
# Course Code      : COSC1283
# Program Code     : MC060
# Start up code provided by Christopher Hoobin and Xiaodong Li
##############################################################################
CFLAGS = -ansi -Wall -pedantic -lm
CC = gcc

vm: vm.o vm_utility.o vm_options.o
	$(CC) $(CFLAGS) -o vm vm.o vm_utility.o vm_options.o
vm.o: vm.c vm.h
	$(CC) $(CFLAGS) -c vm.c
vm_options.o: vm_options.c vm_options.h
	$(CC) $(CFLAGS) -c vm_options.c
vm_utility.o: vm_utility.c vm_utility.h
	$(CC) $(CFLAGS) -c vm_utility.c
clean:
	rm -rf *.o core vm *.errs
archive:
	zip $(USER)-a1.zip *.c *.txt *.csv *.h makefile
