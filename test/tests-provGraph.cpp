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

TEST(provGraph, split_precompute_node) {
  
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
    predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
    // predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 5)));
   
    ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i1, A(i) += precomputed(i1)), 
                                                forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
                                                predicate));

    // ProvenanceGraph provGraph = (stmt.concretize());

   cout << "PRINT WRT PARENTS" << endl; 
   provGraph.printGraphParent();
   cout << "***********************" << endl; 
   cout << "PRINT WRT CHILD" << endl; 
   provGraph.printGraphChild();
   cout << "***********************" << endl; 

}

TEST(provGraph, split_precompute_parent_node) {
  
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
  predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
  predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 5)));
  
  ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
                                                forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
                                                predicate));

   cout << "PRINT WRT PARENTS" << endl; 
   provGraph.printGraphParent();
   cout << "***********************" << endl; 
   cout << "PRINT WRT CHILD" << endl; 
   provGraph.printGraphChild();
   cout << "***********************" << endl; 

}

//the statement does not match up to 
//the predicates

TEST(provGraph, fuse_precompute_node) {
  
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
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"),i4("i4"), iw("iw"), iw1("iw1"), iw2("iw2");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

  std::vector<IndexVarRel> predicate;
  predicate.push_back(IndexVarRel(new FuseRelNode(i0, i1, i2)));
  predicate.push_back(IndexVarRel(new PrecomputeRelNode(i2, iw)));
  predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
  predicate.push_back(IndexVarRel(new SplitRelNode(i2, i3, i4, 2)));
  
  ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
                                              forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
                                              predicate));

   cout << "PRINT WRT PARENTS" << endl; 
   provGraph.printGraphParent();
   cout << "***********************" << endl; 
   cout << "PRINT WRT CHILD" << endl; 
   provGraph.printGraphChild();
   cout << "***********************" << endl; 

}

//the statement does not match up to 
//the predicates

TEST(provGraph, multiple_precompute) {
  
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
  IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"),i4("i4"), iw("iw"), iw1("iw1"), iw2("iw2"), \
            iww("iww"), iww1("iww1"), iww2("iww2");
  IndexExpr precomputedExpr = B(i) * C(i);
  A(i) = precomputedExpr;

  IndexStmt stmt = A.getAssignment().concretize();
  TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

  std::vector<IndexVarRel> predicate;
  predicate.push_back(IndexVarRel(new SplitRelNode(i, i0, i1, 5)));
  predicate.push_back(IndexVarRel(new PrecomputeRelNode(i1, iw)));
  predicate.push_back(IndexVarRel(new SplitRelNode(iw, iw1, iw2, 2)));
  predicate.push_back(IndexVarRel(new SplitRelNode(i1, i2, i3, 5)));
  predicate.push_back(IndexVarRel(new PrecomputeRelNode(iw2, iww)));
  predicate.push_back(IndexVarRel(new SplitRelNode(iww, iww1, iww2, 2)));
  
  ProvenanceGraph provGraph = ProvenanceGraph(suchthat(forall(i0, where(forall(i2, forall(i3, A(i) += precomputed(i1)) ), 
                                              forall(iw1, forall(iw2, precomputed(iw) += B(i) * C(i))) )), 
                                              predicate));

   cout << "PRINT WRT PARENTS" << endl; 
   provGraph.printGraphParent();
   cout << "***********************" << endl; 
   cout << "PRINT WRT CHILD" << endl; 
   provGraph.printGraphChild();
   cout << "***********************" << endl; 

}


