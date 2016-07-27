deck2bolt: deck2bolt.c
	$(CC) -o deck2bolt deck2bolt.c -lm

clean:
	rm -f deck2bolt
