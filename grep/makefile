all: my_grep

my_grep:
	gcc -Wall -Werror -Wextra -D_GNU_SOURCE my_grep.c -o my_grep

sanit:
	gcc -Wall -Werror -Wextra -g -fsanitize=address -D_GNU_SOURCE my_grep.c -o my_grep

test:
	./my_grep -e they file.txt file1.txt > zel_new.txt && grep -e they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -c they file.txt file1.txt > zel_new.txt && grep -c they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -i they file.txt file1.txt > zel_new.txt && grep -i they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -v they file.txt file1.txt > zel_new.txt && grep -v they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -l they file.txt file1.txt > zel_new.txt && grep -l they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -n they file.txt file1.txt > zel_new.txt && grep -n they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -h they file.txt file1.txt > zel_new.txt && grep -h they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -s they file.txt file1.txt > zel_new.txt && grep -s they file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	./my_grep -f template.txt file.txt file1.txt > zel_new.txt && grep -f template.txt file.txt file1.txt > zel_orig.txt && diff zel_new.txt zel_orig.txt
	

check:
	python3 cpplint.py --extensions=c my_grep.c

clean:
	rm my_grep
	rm zel_new.txt
	rm zel_orig.txt

leaks:
	leaks -atExit -- ./my_grep
