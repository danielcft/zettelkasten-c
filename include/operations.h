
struct context {
	char* zet_dir;
	char* editor;
};


void add(struct context ctx);
void delete(struct context ctx, char *id);
void edit(struct context ctx, char *id);
void grep(struct context ctx, char *regexp);
void ls(struct context ctx);
void view(struct context ctx, char *id);
