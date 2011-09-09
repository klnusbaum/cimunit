/**
 * newTest should be null
 */
int cimunit_create_test_instance(
  int (*test_func)(void *),
  cimunit_schedule *sc,
  cimunit_test_instance *newTest )
{
  cimunit_test_instance *newTest = (cimunit_test_instance*)malloc(
    sizeof(cimunit_test_instance));
  newTest->test_function = test_func;
  newTest->sc = sc;
  newTest->next = NULL;
}

cimunit_queue_test(
  cimunit_test_instance* newTest, 
  cimunit_tester *tester)
{
  if(headTest == NULL){
    headTest = newTest;
    tailTest = tailTest;
  }
  else{
    tailTest->next = newTest;
    tailTest = newTest;
  }
}

int cimunit_add_test(
  cimunit_tester *tester, 
  int (*test_func)(void *),
  cimunit_schedule* sc )
{
  cimunit_test_instance *newTest;
  cimunit_create_test_instance(test_func, sc, newTest);
  cimunit_queue_test(newTest, tester);
}

