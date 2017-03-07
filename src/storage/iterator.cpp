#include "iterator.h"

#include "tensor_base.h"
#include "expr.h"
#include "ir/ir.h"

#include "root_iterator.h"
#include "dense_iterator.h"
#include "sparse_iterator.h"

using namespace std;

namespace taco {
namespace storage {

// class Iterator
Iterator::Iterator() : iterator(nullptr) {
}

Iterator Iterator::makeRoot(const ir::Expr& tensor) {
  Iterator iterator;
  iterator.iterator = std::make_shared<RootIterator>(tensor);
  return iterator;
}

Iterator Iterator::make(string name, const ir::Expr& tensorVar,
                        int level, Level levelFormat, Iterator parent,
                        const TensorBase& tensor) {
  Iterator iterator;

  // TODO: Remove
  switch (levelFormat.getType()) {
    case LevelType::Dense: {
      size_t dimSize = tensor.getDimensions()[levelFormat.getDimension()];
      iterator.iterator =
          std::make_shared<DenseIterator>(name, tensorVar, level, dimSize,
                                          parent);
      break;
    }
    case LevelType::Sparse:
      iterator.iterator =
          std::make_shared<SparseIterator>(name, tensorVar, level, parent);
      break;
    case LevelType::Fixed:
      break;
  }
  iassert(iterator.defined());
  return iterator;
}

const Iterator& Iterator::getParent() const {
  return iterator->getParent();
}

bool Iterator::isRandomAccess() const {
  iassert(defined());
  return iterator->isRandomAccess();
}

bool Iterator::isSequentialAccess() const {
  iassert(defined());
  return iterator->isSequentialAccess();
}

ir::Expr Iterator::getTensor() const {
  iassert(defined());
  return iterator->getTensor();
}

ir::Expr Iterator::getPtrVar() const {
  iassert(defined());
  return iterator->getPtrVar();
}

ir::Expr Iterator::getIdxVar() const {
  iassert(defined());
  return iterator->getIdxVar();
}

ir::Expr Iterator::getIteratorVar() const {
  iassert(defined());
  return iterator->getIteratorVar();
}

ir::Expr Iterator::begin() const {
  iassert(defined());
  return iterator->begin();
}

ir::Expr Iterator::end() const {
  iassert(defined());
  return iterator->end();
}

ir::Stmt Iterator::initDerivedVar() const {
  iassert(defined());
  return iterator->initDerivedVars();
}

ir::Stmt Iterator::storePtr() const {
  iassert(defined());
  return iterator->storePtr();
}

ir::Stmt Iterator::storeIdx(ir::Expr idx) const {
  iassert(defined());
  return iterator->storeIdx(idx);
}

ir::Stmt Iterator::resizePtrStorage(ir::Expr size) const {
  iassert(defined());
  return iterator->resizePtrStorage(size);
}

ir::Stmt Iterator::resizeIdxStorage(ir::Expr size) const {
  iassert(defined());
  return iterator->resizeIdxStorage(size);
}

bool Iterator::defined() const {
  return iterator != nullptr;
}

std::ostream& operator<<(std::ostream& os, const Iterator& iterator) {
  if (!iterator.defined()) {
    return os << "Iterator()";
  }
  return os << iterator.getPtrVar();
}


// class IteratorImpl
IteratorImpl::IteratorImpl(Iterator parent, ir::Expr tensor) :
    parent(parent), tensor(tensor) {
}

IteratorImpl::~IteratorImpl() {
}

const Iterator& IteratorImpl::getParent() const {
  return parent;
}

const ir::Expr& IteratorImpl::getTensor() const {
  return tensor;
}

}}
