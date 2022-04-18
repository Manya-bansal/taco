#include <taco/index_notation/transformations.h>
#include <codegen/codegen_c.h>
#include <codegen/codegen_cuda.h>
#include "test.h"
#include "test_tensors.h"
#include "taco/tensor.h"
#include "taco/index_notation/index_notation.h"
#include "codegen/codegen.h"
#include "taco/lower/lower.h"

using namespace taco;

// TEST(provGraph, split_precompute_node) {
  
//   Tensor<double> A("A", {16}, Format{Dense});
//   Tensor<double> B("B", {16}, Format{Dense});
//   Tensor<double> C("C", {16}, Format{Dense});

//   for (int i = 0; i < 16; i++) {
//       A.insert({i}, (double) i);
//       B.insert({i}, (double) i);
//   }

//   A.pack();
//   B.pack();

//   IndexVar i("i");
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw"), iw1("iw1"), iw2("iw2");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

//     std::vector<IndexVarRel> predicate;
//     predicate.push_back(IndexVarRel(new SplitRelNode(i, i0, i1, 5)));
//     predicate.push_back(IndexVarRel(new PrecomputeRelNode(i1, iw)));
//     predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
//     // predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 5)));
   
//     ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i1, A(i) += precomputed(i1)), 
//                                                 forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
//                                                 predicate));

//     // ProvenanceGraph provGraph = (stmt.concretize());

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }

// TEST(provGraph, split_precompute_parent_node) {
  
//   Tensor<double> A("A", {16}, Format{Dense});
//   Tensor<double> B("B", {16}, Format{Dense});
//   Tensor<double> C("C", {16}, Format{Dense});

//   for (int i = 0; i < 16; i++) {
//       A.insert({i}, (double) i);
//       B.insert({i}, (double) i);
//   }

//   A.pack();
//   B.pack();

//   IndexVar i("i");
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw"), iw1("iw1"), iw2("iw2");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);


//   std::vector<IndexVarRel> predicate;
//   predicate.push_back(IndexVarRel(new SplitRelNode(i, i0, i1, 5)));
//   predicate.push_back(IndexVarRel(new PrecomputeRelNode(i1, iw)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 5)));
  
//   ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
//                                                 forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
//                                                 predicate));

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }

// //the statement does not match up to 
// //the predicates
// TEST(provGraph, fuse_precompute_node) {
  
//   Tensor<double> A("A", {16}, Format{Dense});
//   Tensor<double> B("B", {16}, Format{Dense});
//   Tensor<double> C("C", {16}, Format{Dense});

//   for (int i = 0; i < 16; i++) {
//       A.insert({i}, (double) i);
//       B.insert({i}, (double) i);
//   }

//   A.pack();
//   B.pack();

//   IndexVar i("i");
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"),i4("i4"), iw("iw"), iw1("iw1"), iw2("iw2");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

//   std::vector<IndexVarRel> predicate;
//   predicate.push_back(IndexVarRel(new FuseRelNode(i0, i1, i2)));
//   predicate.push_back(IndexVarRel(new PrecomputeRelNode(i2, iw)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(i2, i3, i4, 2)));
  
//   ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
//                                               forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
//                                               predicate));

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }

// //the statement does not match up to 
// //the predicates
// TEST(provGraph, multiple_precompute) {
  
//   Tensor<double> A("A", {16}, Format{Dense});
//   Tensor<double> B("B", {16}, Format{Dense});
//   Tensor<double> C("C", {16}, Format{Dense});

//   for (int i = 0; i < 16; i++) {
//       A.insert({i}, (double) i);
//       B.insert({i}, (double) i);
//   }

//   A.pack();
//   B.pack();

//   IndexVar i("i");
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"),i4("i4"), iw("iw"), iw1("iw1"), iw2("iw2"), \
//             iww("iww"), iww1("iww1"), iww2("iww2");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

//   std::vector<IndexVarRel> predicate;
//   predicate.push_back(IndexVarRel(new SplitRelNode(i, i0, i1, 5)));
//   predicate.push_back(IndexVarRel(new PrecomputeRelNode(i1, iw)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 5)));
//   predicate.push_back(IndexVarRel(new PrecomputeRelNode(iw2, iww)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(iww, iww1, iww2, 2)));
  
//   ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
//                                               forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
//                                               predicate));

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }

// TEST(provGraph, fuse_pos_node) {
  
//   Tensor<double> A("A", {16}, Format{Dense});
//   Tensor<double> B("B", {16}, Format{Dense});
//   Tensor<double> C("C", {16}, Format{Dense});

//   for (int i = 0; i < 16; i++) {
//       A.insert({i}, (double) i);
//       B.insert({i}, (double) i);
//   }

//   A.pack();
//   B.pack();

//   IndexVar i("i");
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), ip1("ip1"),ip2("ip2"), iw("iw"), iw1("iw1"), iw2("iw2"), \
//             iww("iww"), iww1("iww1"), iww2("iww2"), ip("ip");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

//   Access access; 

//   std::vector<IndexVarRel> predicate;
//   predicate.push_back(IndexVarRel(new FuseRelNode(i0, i1, i2)));
//   predicate.push_back(IndexVarRel(new PrecomputeRelNode(i2, iw)));
//   predicate.push_back(IndexVarRel(new PosRelNode(i2, ip, access)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
//   predicate.push_back(IndexVarRel(new PrecomputeRelNode(ip, iww)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(iww, iww1, iww2, 2)));
//   predicate.push_back(IndexVarRel(new SplitRelNode(ip, ip1, ip2, 2)));

//   ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
//                                               forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
//                                               predicate));

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }



TEST(provGraph, isRecoverableSinglePrecompute){

  Tensor<double> A("A", {16}, Format{Dense});
  Tensor<double> B("B", {16}, Format{Dense});
  Tensor<double> C("C", {16}, Format{Dense});

  for (int i = 0; i < 16; i++) {
      A.insert({i}, (double) i);
      B.insert({i}, (double) i);
  }

  A.pack();
  B.pack();

  IndexVar i("i");
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw"), iw1("iw1"), iw2("iw2");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

  std::vector<IndexVarRel> predicate;
  predicate.push_back(IndexVarRel(new SplitRelNode(i, i0, i1, 5)));
  predicate.push_back(IndexVarRel(new PrecomputeRelNode(i1, iw)));
  predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 2)));


  ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
                                                forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
                                                predicate));
  ASSERT_TRUE(provGraph.isConsumer(i1));
  ASSERT_TRUE(provGraph.isProducer(iw));


  std::set<IndexVar> defined;

  defined.insert(i0);
  defined.insert(i1);

  ASSERT_TRUE(provGraph.isRecoverable(i, defined));

  std::set<IndexVar> defined2;

  defined2.insert(i0);
  defined2.insert(iw);

  ASSERT_TRUE(provGraph.isRecoverable(i, defined2));

  std::set<IndexVar> defined3;

  defined3.insert(i0);
  defined3.insert(i2);
  ASSERT_TRUE(!provGraph.isRecoverable(i, defined3));
  
  defined3.insert(i3);
  ASSERT_TRUE(provGraph.isRecoverable(i, defined3));

}



TEST(provGraph, isRecoverableSinglePrecomputeSplit){

  Tensor<double> A("A", {16}, Format{Dense});
  Tensor<double> B("B", {16}, Format{Dense});
  Tensor<double> C("C", {16}, Format{Dense});

  for (int i = 0; i < 16; i++) {
      A.insert({i}, (double) i);
      B.insert({i}, (double) i);
  }

  A.pack();
  B.pack();

  IndexVar i("i");
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw"), iw1("iw1"), iw2("iw2");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

  std::vector<IndexVarRel> predicate;
  predicate.push_back(IndexVarRel(new SplitRelNode(i, i0, i1, 5)));
  predicate.push_back(IndexVarRel(new PrecomputeRelNode(i1, iw)));
  predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 2)));
  predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));


  ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
                                                forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
                                                predicate));
  ASSERT_TRUE(provGraph.isConsumer(i1));
  ASSERT_TRUE(provGraph.isProducer(iw));


  std::set<IndexVar> defined;

  defined.insert(i0);
  defined.insert(i1);

  ASSERT_TRUE(provGraph.isRecoverable(i, defined));

  std::set<IndexVar> defined2;

  defined2.insert(i0);

  ASSERT_TRUE(!provGraph.isRecoverable(i, defined2)); 

  defined2.insert(iw);

  ASSERT_TRUE(provGraph.isRecoverable(i, defined2));

  std::set<IndexVar> defined3;

  defined3.insert(i0);
  defined3.insert(i2);

  ASSERT_TRUE(!provGraph.isRecoverable(i, defined3)); 

  defined3.insert(i3);

  ASSERT_TRUE(provGraph.isRecoverable(i, defined3)); 

  std::set<IndexVar> defined4;

  defined4.insert(i0);
  defined4.insert(iw2);

  ASSERT_TRUE(!provGraph.isRecoverable(i, defined4));

  defined4.insert(iw1);

  ASSERT_TRUE(provGraph.isRecoverable(i, defined4));

}


TEST(provGraph, indexConcrete1) {
  
  Tensor<double> A("A", {16}, Format{Dense});
  Tensor<double> B("B", {16}, Format{Dense});
  Tensor<double> C("C", {16}, Format{Dense});

  for (int i = 0; i < 16; i++) {
      A.insert({i}, (double) i);
      B.insert({i}, (double) i);
  }

  A.pack();
  B.pack();

  IndexVar i("i");
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), ip1("ip1"),ip2("ip2"), iw("iw"), iw1("iw1"), iw2("iw2"), \
            iww("iww"), iww1("iww1"), iww2("iww2"), ip("ip");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);


  //should not throw an error

  stmt = stmt.bound(i, 18, BoundType::MaxExact)
             .split(i, i0, i1, 5)
             .precompute(precomputedExpr, i1, iw, precomputed)
             .split(i1, i2, i3, 2);
}



TEST(provGraph, indexConcrete2) {
  
  Tensor<double> A("A", {16}, Format{Dense});
  Tensor<double> B("B", {16}, Format{Dense});
  Tensor<double> C("C", {16}, Format{Dense});

  for (int i = 0; i < 16; i++) {
      A.insert({i}, (double) i);
      B.insert({i}, (double) i);
  }

  A.pack();
  B.pack();

  IndexVar i("i");
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), ip1("ip1"),ip2("ip2"), iw("iw"), iw1("iw1"), iw2("iw2"), \
            iww("iww"), iww1("iww1"), iww2("iww2"), ip("ip");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);


  //should not throw an error
  stmt = stmt.bound(i, 18, BoundType::MaxExact)
             .split(i, i0, i1, 5)
             .precompute(precomputedExpr, i1, iw, precomputed)
             .split(i1, i2, i3, 2)
             .split(iw, iw1, iw2, 2);
}


TEST(provGraph, indexConcreteMultiplePrecompute) {
  
  Tensor<double> A("A", {16}, Format{Dense});
  Tensor<double> B("B", {16}, Format{Dense});
  Tensor<double> C("C", {16}, Format{Dense});

  for (int i = 0; i < 16; i++) {
      A.insert({i}, (double) i);
      B.insert({i}, (double) i);
  }

  A.pack();
  B.pack();

  IndexVar i("i");
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), ip1("ip1"),ip2("ip2"), iw("iw"), iw1("iw1"), iw2("iw2"), \
            iww("iww"), iww1("iww1"), iww2("iww2"), ip("ip");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);


  //should not throw an error
  stmt = stmt.bound(i, 18, BoundType::MaxExact)
             .split(i, i0, i1, 5)
             .precompute(precomputedExpr, i1, iw, precomputed)
             .split(i1, i2, i3, 2)
             .split(iw, iw1, iw2, 2)
             .precompute(precomputedExpr, iw, iww, precomputed);
            // .split(iww, iww1, iww2, 2); fails

  ProvenanceGraph provGraph =  ProvenanceGraph(stmt);


  std::set<IndexVar> defined;

  defined.insert(iww);
  ASSERT_TRUE(!provGraph.isRecoverable(i, defined));
    
  defined.insert(i0);
  ASSERT_TRUE(provGraph.isRecoverable(i, defined));

}






