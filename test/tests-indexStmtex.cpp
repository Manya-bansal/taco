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

TEST(stmt_ex, example0){
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
             .split(i1, i2, i3, 2)
             .fuse(i2, i3, iw);
            // .split(iww, iww1, iww2, 2); fails

  cout << stmt << endl;


}

TEST(stmt_ex, example2) {
  Tensor<double> A("A", {8}, Format({Sparse}));
  Tensor<double> B("B", {8}, Format({Sparse}));
  Tensor<double> C("C", {8}, Format({Dense}));

  for (int i = 0; i < 8; i++) {
    if (i % 2 == 0) {
      A.insert({i}, (double) i);
    }
    if (i != 2 && i != 3 && i != 4) {
      B.insert({i}, (double) i);
    }
  }

  A.pack();
  B.pack();

  IndexVar i("i"), ipos("ipos"), ipos1("ipos1");
  C(i) = A(i) * B(i);

  IndexStmt stmt = C.getAssignment().concretize();
  stmt = stmt.pos(i, ipos, A(i))
        .pos(ipos, ipos1, A(i));

  cout << stmt << endl;

}