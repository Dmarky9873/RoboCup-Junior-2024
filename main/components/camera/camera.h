#include <SPI.h>
#include <Pixy2.h>

struct Camera {
  Pixy2 pixy;
  int32_t centerX;
  int32_t centerY;
  int32_t middleThreshold;

  Camera() {
    pixy.init();
    centerX = pixy.frameWidth / 2;
    centerY = pixy.frameHeight / 2;
    middleThreshold = 100;
  }

  String getObjectDirection() {
    int32_t blocks;
    blocks = pixy.ccc.getBlocks();

    if (blocks) {
      int32_t midX = pixy.ccc.blocks[0].m_x;l
      int32_t midY = pixy.ccc.blocks[0].m_y;

      if (midX > centerX - middleThreshold && midX < centerX + middleThreshold && midY > centerY - middleThreshold && midY < centerY + middleThreshold) {
        return "In line with net";
      } else {
        if (midX < centerX) {
          return "Net on left side";
        } else {
          return "Net on right side";
        }
      }
    } else {
      return "Net is Not Detected";
    }
  }
};
