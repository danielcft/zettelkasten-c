OUTDIR=.build
INCLUDE+=-Iinclude
C_STANDARD=c17

OBJECTS=\
	$(OUTDIR)/main.o \
	$(OUTDIR)/io.o \
	$(OUTDIR)/env.o \
	$(OUTDIR)/grep.o \
	$(OUTDIR)/add.o \
	$(OUTDIR)/delete.o \
	$(OUTDIR)/edit.o \
	$(OUTDIR)/view.o


$(OUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTDIR)
	$(CC) -std=$(C_STANDARD) -pedantic -c -o $@ $(CFLAGS) $(MAINFLAGS) $(INCLUDE) $<

zettelkasten: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OUTDIR) zettelkasten

