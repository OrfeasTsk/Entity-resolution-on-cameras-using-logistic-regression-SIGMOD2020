#include "../include/acutest.h"
#include "../include/all_tests.h"



//Pinakas me tests
TEST_LIST = {
	{ "parse_test", check_parse },
	{ "cutoffdictionary_test", check_CutOffDictionary },
	{ "textcleaning_test", check_textcleaning },
	{ "InsertWord_test", check_InsertWord },
	{ "read_stopwords_test", check_read_stopwords },
	{"tokenization_test", check_tokenization},
	{ "heap_create", test_heapcreate },
	{ "heap_insert", test_heapinsert},
	{ "heapnode_create", test_heapnodecreate },
	{ "swap_heapnodes", test_swap },
	{ "heapify_words", test_heapifywords },
	{ "heap_remove", test_heapremovefirst},
	{ "ht_create", test_htcreate },
	{ "ht_insert", test_htinsert },
	{"ht_merge", test_htmerge },
	{ "queue_create", test_qcreate },
	{ "queue_insert", test_qinsert },
	{ "queue_concat", test_qconcat },
	{ "rbt_create", test_rbtcreate },
	{ "rbt_insert", test_rbtinsert },
	{ "stack_create", test_stcreate },
	{ "stack_push", test_stpush },
	{ "stack_check", test_stcheck },
	{ "initialize_scheduler", test_initializeSchelduler},
	{"jobs_tasks", test_jobs},
	{ NULL, NULL } // NULL sto telos
};
