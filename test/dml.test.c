
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libsr.h>
#include <libst.h>
#include <sophia.h>

static void
dml_precreate(stc *cx srunused)
{
	rmrf(cx->suite->logdir);
	rmrf(cx->suite->dir);
	void *env = sp_env();
	t( env != NULL );
	void *c = sp_ctl(env);
	t( c != NULL );
	t( sp_set(c, "db.test.logdir", cx->suite->logdir) == 0 );
	t( sp_set(c, "db.test.dir", cx->suite->dir) == 0 );
	t( sp_set(c, "db.test.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "db.test.threads", "0") == 0 );
	void *db = sp_get(c, "db.test");
	t( db != NULL );
	t( sp_open(env) == 0 );
	t( sp_destroy(env) == 0 );
}

static void
dml_create_online0(stc *cx srunused)
{
	rmrf(cx->suite->logdir);
	rmrf(cx->suite->dir);
	void *env = sp_env();
	t( env != NULL );
	t( sp_open(env) == 0 );
	void *c = sp_ctl(env);
	t( c != NULL );
	t( sp_set(c, "db.test.logdir", cx->suite->logdir) == 0 );
	t( sp_set(c, "db.test.dir", cx->suite->dir) == 0 );
	t( sp_set(c, "db.test.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "db.test.threads", "0") == 0 );
	void *db = sp_get(c, "db.test");
	t( db != NULL );
	t( sp_open(db) == 0 );
	t( sp_destroy(env) == 0 );
}

static void
dml_create_online1(stc *cx srunused)
{
	rmrf(cx->suite->logdir);
	rmrf(cx->suite->dir);
	void *env = sp_env();
	t( env != NULL );
	t( sp_open(env) == 0 );
	void *c = sp_ctl(env);
	t( c != NULL );
	t( sp_set(c, "db.test.logdir", cx->suite->logdir) == 0 );
	t( sp_set(c, "db.test.dir", cx->suite->dir) == 0 );
	t( sp_set(c, "db.test.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "db.test.threads", "0") == 0 );
	void *db = sp_get(c, "db.test");
	t( db != NULL );
	t( sp_open(db) == 0 );
	t( sp_destroy(db) == 0 );
	t( sp_destroy(env) == 0 );
}

static void
dml_create_online2(stc *cx srunused)
{
	rmrf("./logdir0");
	rmrf("./dir0");
	rmrf("./logdir1");
	rmrf("./dir1");

	void *env = sp_env();
	t( env != NULL );
	t( sp_open(env) == 0 );

	void *c = sp_ctl(env);
	t( c != NULL );
	t( sp_set(c, "db.s0.logdir", "logdir0") == 0 );
	t( sp_set(c, "db.s0.dir", "dir0") == 0 );
	t( sp_set(c, "db.s0.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "db.s0.threads", "0") == 0 );
	void *s0 = sp_get(c, "db.s0");
	t( s0 != NULL );
	t( sp_open(s0) == 0 );

	int key = 7;
	void *o = sp_object(s0);
	sp_set(o, "key", &key, sizeof(key));
	t( sp_set(s0, o) == 0 );
	key = 8;
	o = sp_object(s0);
	sp_set(o, "key", &key, sizeof(key));
	t( sp_set(s0, o) == 0 );
	key = 9;
	o = sp_object(s0);
	sp_set(o, "key", &key, sizeof(key));
	t( sp_set(s0, o) == 0 );

	t( sp_set(c, "db.s1.logdir", "logdir1") == 0 );
	t( sp_set(c, "db.s1.dir", "dir1") == 0 );
	t( sp_set(c, "db.s1.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "db.s1.threads", "0") == 0 );
	void *s1 = sp_get(c, "db.s1");
	t( s0 != NULL );
	t( sp_open(s1) == 0 );

	key = 7;
	o = sp_object(s0);
	sp_set(o, "key", &key, sizeof(key));
	t( sp_set(s1, o) == 0 );
	key = 8;
	o = sp_object(s0);
	sp_set(o, "key", &key, sizeof(key));
	t( sp_set(s1, o) == 0 );
	key = 9;
	o = sp_object(s0);
	sp_set(o, "key", &key, sizeof(key));
	t( sp_set(s1, o) == 0 );

	t( sp_destroy(s1) == 0 );
	t( sp_destroy(s0) == 0 );
	t( sp_destroy(env) == 0 );

	rmrf("./logdir0");
	rmrf("./dir0");
	rmrf("./logdir1");
	rmrf("./dir1");
}

st *dml_group(void)
{
	st *group = st_def("dml", NULL);
	st_test(group, st_def("precreate", dml_precreate));
	st_test(group, st_def("create_online0", dml_create_online0));
	st_test(group, st_def("create_online1", dml_create_online1));
	st_test(group, st_def("create_online2", dml_create_online2));
	return group;
}
