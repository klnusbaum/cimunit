//
// cimunit_example.cpp
//
// Copyright 2011 Dale Frampton and Kurtis Nusbaum
// 
// This file is part of cimunit.
// 
// cimunit is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// cimunit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with cimunit.  If not, see <http://www.gnu.org/licenses/>.
// 

#include <vxworks.h>
#include <deque>
#include <semLib.h>
#include <stdexcept>
#include <taskLib.h>

#include "cimunit.h"
#include "cppunit/extensions/HelperMacros.h"

template<class T>
class ThreadStack {
  public:
    ThreadStack() {
      m_mutex = semMCreate(SEM_Q_FIFO); 
      if (!m_mutex) {
        throw std::runtime_error("Unable to create mutex");
      }
    };
    
    void push(T item) {
      semTake(m_mutex, WAIT_FOREVER);
      m_container.push_front(item);
      semGive(m_mutex);
    }
    
    T pop() {
      semTake(m_mutex, WAIT_FOREVER);
      T item = m_container.front();
      CIMUNIT_FIRE("TS::pop/1");
      m_container.pop_front();
      semGive(m_mutex);
      return item;
    }
    
    bool empty() {
      semTake(m_mutex, WAIT_FOREVER);
      bool result = m_container.empty();
      semGive(m_mutex);
      return result;
    }
    
  private:
    std::deque<T> m_container;
    SEM_ID m_mutex;
    
  
};


// Example of using CIMUnit under VxWorks
class CimunitExample : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CimunitExample);
  CPPUNIT_TEST(singleThreaded);
  CPPUNIT_TEST(multiThreadedStress);
  CPPUNIT_TEST(cimunitStressTest);
  CPPUNIT_TEST(cimunitWhiteBoxTest);
  CPPUNIT_TEST_SUITE_END();

public:
  // Initializes the loopback driver and the driver interface void setUp();
  void setUp();

  // Removes the driver interface and disables the loopback driver 
  void tearDown();

  // Single threaded test used to show proper operation of stack in a single
  // threaded environment.
  void singleThreaded();
  
  // Stress test used to show proper operation of the stack in a
  // multithreaded environment.  This test doesn't use CIMUnit.
  //
  // Since VxWorks will not preempt a higher priority thread it is difficult
  // creating a test that will product an interesting result.
  void multiThreadedStress();
  
  // Rewrite of the multithreaded test using CIMUnit
  //
  // Since VxWorks will not preempt a higher priority thread it is difficult
  // creating a test that will product an interesting result.
  void cimunitStressTest();
  
  // White-box testing of CIMUnit used to produce an 'interesting' schedule.
  // Remove the mutex's surround the operations of the stack to see this test
  // fail.
  void cimunitWhiteBoxTest();
};


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(CimunitExample);


void CimunitExample::setUp() { }
void CimunitExample::tearDown() { } 


void CimunitExample::singleThreaded() {
  ThreadStack<int> testStack;
  
  // Stack is initialized empty
  CPPUNIT_ASSERT_EQUAL(true, testStack.empty());
  
  // Add item, verify stack isn't empty
  testStack.push(100);
  CPPUNIT_ASSERT_EQUAL(false, testStack.empty());
  
  // Add another item.  Pop item and verify LIFO operation and that the stack
  // isn't empty
  testStack.push(200);
  CPPUNIT_ASSERT_EQUAL(200, testStack.pop());
  CPPUNIT_ASSERT_EQUAL(false, testStack.empty());
  
  // Pop last item and verify the stack is now empty
  CPPUNIT_ASSERT_EQUAL(100, testStack.pop());
  CPPUNIT_ASSERT_EQUAL(true, testStack.empty());
}


void stressThread(void *param, int delay, int count) {
  ThreadStack<int> *stack = (ThreadStack<int> *)param;
  // Loop to create lots of demand on the structure
  for(int a = 0; a < count; ++a) {
    stack->push(a);
    // Add delay to hopefully create come interesting interleavings
    taskDelay(delay);
    stack->pop();
  }
}


void CimunitExample::multiThreadedStress() {
  ThreadStack<int> stack;
  
  int id1 = taskSpawn("stress1", 100, 0, 8192, (FUNCPTR)stressThread,
                      (int)(&stack), 0, 60, 0, 0, 0, 0, 0, 0, 0);
  int id2 = taskSpawn("stress2", 99, 0, 8192, (FUNCPTR)stressThread,
                      (int)(&stack), 1, 10, 0, 0, 0, 0, 0, 0, 0);
  
  taskDelay(30);
  
  CPPUNIT_ASSERT_EQUAL(true, stack.empty());
}


void cimunitStressThread1(void *param, int delay) {
  ThreadStack<int> *stack = (ThreadStack<int> *)param;
  // Loop to create lots of demand on the structure
  for(int a = 0; a < 1000; ++a) {
    stack->push(a);
    // Add delay to hopefully create come interesting interleavings
    taskDelay(delay);
    stack->pop();
  }
  CIMUNIT_FIRE("cimunitStressThread1/end");
}


void cimunitStressThread2(void *param, int delay) {
  ThreadStack<int> *stack = (ThreadStack<int> *)param;
  // Loop to create lots of demand on the structure
  for(int a = 0; a < 1000; ++a) {
    stack->push(a);
    // Add delay to hopefully create come interesting interleavings
    taskDelay(delay);
    stack->pop();
  }
  CIMUNIT_FIRE("cimunitStressThread2/end");
}


void CimunitExample::cimunitStressTest() {
  ThreadStack<int> stack;
  
  CIMUNIT_SCHEDULE("(cimunitStressThread1/end && cimunitStressThread2/end)->testDone");
  
  // Two different methods are used as native thread name support hasn't been
  // added to VxWorks.
  int id1 = taskSpawn("stress1", 100, 0, 8192, (FUNCPTR)cimunitStressThread1,
                      (int)(&stack), 0, 60, 0, 0, 0, 0, 0, 0, 0);
  int id2 = taskSpawn("stress2", 99, 0, 8192, (FUNCPTR)cimunitStressThread2,
                      (int)(&stack), 1, 10, 0, 0, 0, 0, 0, 0, 0);
  
  // Event to detect when the test has been completed
  CIMUNIT_FIRE("testDone");
  
  // Verify proper operation of the queue (the queue is empty at the end)
  CPPUNIT_ASSERT_EQUAL(true, stack.empty());
}


void cimunitWhiteBoxTestThread1(void *param) {
  ThreadStack<int> *stack = (ThreadStack<int> *)param;
  
  // Add an item to the queue and then remove it
  stack->push(100);
  stack->pop();
  
  CIMUNIT_FIRE("thread1Done");
}


void cimunitWhiteBoxTestThread2(void *param1, void *param2) {
  ThreadStack<int> *stack = (ThreadStack<int> *)param1;
  bool *result = (bool *)param2;

  CIMUNIT_FIRE("step1");
  // Check if the queue is empty
  *result = stack->empty();

  CIMUNIT_FIRE("thread2Done");
}


void CimunitExample::cimunitWhiteBoxTest() {
  ThreadStack<int> stack;
  bool result = false;
  
  // This schedule attempts to execute the ThreadStack::empty() method
  // while in the middle of the ThreadStack::pop() method.
  CIMUNIT_SCHEDULE("TS::pop/1->step1,(thread1Done&&thread2Done)->testDone");
  
  // This thread is of a lower priority which ensures that the pop
  // operation isn't completed before the other thread checks if the stack
  // is empty.
  int id1 = taskSpawn("test1", 100, 0, 8192, (FUNCPTR)cimunitWhiteBoxTestThread1,
                      (int)(&stack), 0, 0, 0, 0, 0, 0, 0, 0, 0);
  int id2 = taskSpawn("test2", 99, 0, 8192, (FUNCPTR)cimunitWhiteBoxTestThread2,
                      (int)(&stack), (int)&result, 0, 0, 0, 0, 0, 0, 0, 0);
  
  // Event to detect when the test has been completed
  CIMUNIT_FIRE("testDone");
  
  // Verify proper operation of the queue by ensuring the queue was detected
  // as empty.
  CPPUNIT_ASSERT_EQUAL(true, result);
}

