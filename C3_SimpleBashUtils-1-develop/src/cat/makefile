all: s21_cat

s21_cat: 
	gcc -Wall -Werror -Wextra s21_cat.c -o s21_cat

test:
	./s21_cat -b file.txt > zel_new.txt && cat -b file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_cat -e file.txt > zel_new.txt && cat -e file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_cat -s file.txt > zel_new.txt && cat -s file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_cat -n file.txt > zel_new.txt && cat -n file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_cat -t file.txt > zel_new.txt && cat -t file.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt

check:
	python3 cpplint.py --extensions=c s21_cat.c

clean:
	rm s21_cat
	rm zel_new.txt
	rm zel_orig.txt

leaks:
	leaks -atExit -- ./s21_cat
