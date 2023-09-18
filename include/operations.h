/* holds environment variables*/
struct environment {
	char *zet_dir; /* ${ZET_DIR} */
	char *editor;  /* ${EDITOR} */
};

/* populate environment variables in environment struct */
void init_env();

/* all these calls assume init_env() being invoked at least once */
void add();
void delete(char *id);
void edit(char *id);
void grep(char *regexp);
void ls();
void view(char *id);

