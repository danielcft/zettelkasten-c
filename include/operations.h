/* holds environment variables*/
struct environment {
	char *zet_dir; /* ${ZET_DIR} */
	char *editor;  /* ${EDITOR} */
};

/* populate environment variables in environment struct */
void init_env(void);

/* all these calls assume init_env() being invoked at least once */
void add(void);
void delete(const char *id);
void edit(const char *id);
void grep(const char *regexp);
void ls(void);
void view(const char *id);

