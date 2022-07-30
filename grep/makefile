all: s21_grep

s21_grep:
	gcc -Wall -Werror -Wextra -D_GNU_SOURCE s21_grep.c -o s21_grep

sanit:
	gcc -Wall -Werror -Wextra -g -fsanitize=address -D_GNU_SOURCE s21_grep.c -o s21_grep

test:
	./s21_grep -e they file.txt file1.txt > zel_new.txt && grep -e they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -c they file.txt file1.txt > zel_new.txt && grep -c they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -i they file.txt file1.txt > zel_new.txt && grep -i they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -v they file.txt file1.txt > zel_new.txt && grep -v they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -l they file.txt file1.txt > zel_new.txt && grep -l they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -n they file.txt file1.txt > zel_new.txt && grep -n they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -h they file.txt file1.txt > zel_new.txt && grep -h they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -s they file.txt file1.txt > zel_new.txt && grep -s they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./s21_grep -f template.txt file.txt file1.txt > zel_new.txt && grep -f template.txt file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	

check:
	python3 cpplint.py --extensions=c s21_grep.c

clean:
	rm s21_grep
	rm zel_new.txt
	rm zel_orig.txt

leaks:
	leaks -atExit -- ./s21_grep
