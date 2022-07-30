all: my_cat

my_cat: 
	gcc -Wall -Werror -Wextra my_cat.c -o my_cat

test:
	./my_cat -b file.txt > zel_new.txt && cat -b file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_cat -e file.txt > zel_new.txt && cat -e file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_cat -s file.txt > zel_new.txt && cat -s file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_cat -n file.txt > zel_new.txt && cat -n file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_cat -t file.txt > zel_new.txt && cat -t file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt

check:
	python3 cpplint.py --extensions=c my_cat.c

clean:
	rm my_cat
	rm zel_new.txt
	rm zel_orig.txt

leaks:
	leaks -atExit -- ./my_cat
