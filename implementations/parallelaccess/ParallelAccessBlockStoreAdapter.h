#ifndef MESSMER_BLOCKSTORE_IMPLEMENTATIONS_PARALLELACCESS_PARALLELACCESSBLOCKSTOREADAPTER_H_
#define MESSMER_BLOCKSTORE_IMPLEMENTATIONS_PARALLELACCESS_PARALLELACCESSBLOCKSTOREADAPTER_H_

#include <messmer/cpp-utils/macros.h>
#include <messmer/parallelaccessstore/ParallelAccessStore.h>
#include "../../interface/BlockStore.h"

namespace blockstore {
namespace parallelaccess {

class ParallelAccessBlockStoreAdapter: public parallelaccessstore::ParallelAccessBaseStore<Block, Key> {
public:
  explicit ParallelAccessBlockStoreAdapter(BlockStore *baseBlockStore)
    :_baseBlockStore(std::move(baseBlockStore)) {
  }

  boost::optional<cpputils::unique_ref<Block>> loadFromBaseStore(const Key &key) override {
    //TODO Don't use nullcheck but make blockstore use unique_ref
	return cpputils::nullcheck(_baseBlockStore->load(key));
  }

  void removeFromBaseStore(cpputils::unique_ref<Block> block) override {
    //TODO Don't use to_unique_ptr but make blockstore use unique_ref
	return _baseBlockStore->remove(cpputils::to_unique_ptr(std::move(block)));
  }

private:
  BlockStore *_baseBlockStore;

  DISALLOW_COPY_AND_ASSIGN(ParallelAccessBlockStoreAdapter);
};

}
}

#endif
