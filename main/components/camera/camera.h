#include <SPI.h>
#include <Pixy2.h>

struct Camera {
  Pixy2 pixy;
  int32_t centerX;
  int32_t middleThreshold;

  Camera() {
    pixy.init();
    centerX = 155;     
    middleThreshold = 50;  
  }

  String getObjectDirection() {
    int32_t blocks;
    blocks = pixy.ccc.getBlocks();

    if (blocks) {
      int32_t midX = pixy.ccc.blocks[0].m_x;

      if (midX > centerX - middleThreshold && midX < centerX + middleThreshold) {
        return "CENTER";  // the camera can see the net directly in front of it
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

  int32_t getDistanceToCenter() {
    int32_t blocks;
    blocks = pixy.ccc.getBlocks();

    if (blocks) {
      int32_t midX = pixy.ccc.blocks[0].m_x;
      int32_t distanceToThreshold = abs(centerX - midX) - middleThreshold;
      return distanceToThreshold;  // Distance from object to threshold
    } else {
      return -1;  // Return a negative value to indicate no object detected
    }
  }

  int32_t getRotationDistance() {
    int32_t distanceToCenter = getDistanceToCenter();
    if (distanceToCenter >= 0) {
      // Calculate how much the robot needs to rotate to align with the threshold
      int32_t rotationDistance = middleThreshold - distanceToCenter;
      return rotationDistance;
    } else {
      return -1;  // No object detected, return a negative value
    }
  }
};
