#ifndef WORLDCONSTANTS_H
#define WORLDCONSTANTS_H

namespace world_const {
    constexpr int CHUNK_SIZE = 33;
    constexpr int BLOCK_SIZE = 1;

    constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
    constexpr int BLOCK_NUMBER = CHUNK_SIZE -1;


}

#endif // WORLDCONSTANTS_H
