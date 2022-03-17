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


// TEST(provGraph, print_provGraph1) {
  
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
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);
//   stmt = stmt.bound(i, 18, BoundType::MaxExact)
//              .bound(i, 16, BoundType::MaxExact)
//              .split(i, i0, i1, 5)
//              .split(i1, i2, i3, 2)
//              .precompute(precomputedExpr, i1, iw, precomputed);

//     ir::IRPrinter irp = ir::IRPrinter(cout);
             
//     cout << stmt << endl;
   
//     ProvenanceGraph provGraph = ProvenanceGraph(stmt.concretize());

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }


TEST(provGraph, print_provGraph2) {
  
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
  stmt = stmt.split(i, i0, i1, 5);
             
             

    ir::IRPrinter irp = ir::IRPrinter(cout);
    cout << stmt << endl;

    cout << "--------" << endl;

    // IndexVarRel rel = IndexVarRel(new SplitRelNode(i, i0, i1, 5));
             


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


// TEST(provGraph, print_provGraph2) {
  
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
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;


//   IndexStmt stmt = A.getAssignment().concretize();

//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);

//   stmt = stmt.bound(i, 18, BoundType::MaxExact)
//              .bound(i, 16, BoundType::MaxExact)
//              .split(i, i0, i1, 5)
//              .precompute(precomputedExpr, i1, iw, precomputed)
//              .split(i1, i2, i3, 2);
            

//     ir::IRPrinter irp = ir::IRPrinter(cout);
             
//     cout << stmt << endl;
   
//     ProvenanceGraph provGraph = ProvenanceGraph(stmt.concretize());

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }



// TEST(provGraph, print_normal_provGraph) {
  
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
//   IndexVar i0("i0"), i1("i1"), i2("i2"), i3("i3"), iw("iw");
//   IndexExpr precomputedExpr = B(i) * C(i);
//   A(i) = precomputedExpr;

//   IndexStmt stmt = A.getAssignment().concretize();
//   TensorVar precomputed("precomputed", Type(Float64, {Dimension(i1)}), taco::dense);
//   stmt = stmt.bound(i, 18, BoundType::MaxExact)
//              .bound(i, 16, BoundType::MaxExact)
//              .split(i, i0, i1, 5)
//              .precompute(precomputedExpr, i1, iw, precomputed);
            

//     ir::IRPrinter irp = ir::IRPrinter(cout);
             
//     cout << stmt << endl;
   
//     ProvenanceGraph provGraph = ProvenanceGraph(stmt.concretize());

//    cout << "PRINT WRT PARENTS" << endl; 
//    provGraph.printGraphParent();
//    cout << "***********************" << endl; 
//    cout << "PRINT WRT CHILD" << endl; 
//    provGraph.printGraphChild();
//    cout << "***********************" << endl; 

// }

