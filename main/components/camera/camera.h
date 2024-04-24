#include <SPI.h>
#include <Pixy2.h>

Pixy2 pixy;

struct Camera {
  int32_t centerX;
  int32_t middleThreshold;
  float fov;
  int32_t frameWidth;

  Camera() {
    pixy.init();
    centerX = pixy.frameWidth / 2;
    middleThreshold = 50;
    fov = 70.0;
    frameWidth = pixy.frameWidth;
  }

  String getObjectDirection() {
    int32_t blocks;
    blocks = pixy.ccc.getBlocks();

    if (blocks) {
      int32_t midX = pixy.ccc.blocks[0].m_x;

      if (midX > centerX - middleThreshold && midX < centerX + middleThreshold) {
        return "CENTER";
      } else {
        if (midX < centerX) {
          return "LEFT";
        } else {
          return "RIGHT";
        }
      }
    } else {
      return "NONE";
    }
  }

  float getRotationDistance() {
    int32_t blocks;
    blocks = pixy.ccc.getBlocks();

    if (blocks) {
      int32_t midX = pixy.ccc.blocks[0].m_x;
      int32_t distanceFromCenter = abs(centerX - midX);
      return ((fov / frameWidth) * distanceFromCenter) * 0.45;
    } else {
      return -1;
    }
  }
};
