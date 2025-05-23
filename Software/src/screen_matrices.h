/**
 * @file screen_matrices.h
 * @brief LED matrix display patterns for robot status indication
 * @author Group C4
 * @date 2025
 */

/**
 * @brief Stop sign pattern for LED matrix
 * 
 * Displays an octagonal stop sign pattern when obstacle is detected
 */
const uint32_t stopSign[] = {
	0xf010820,
	0x42f42f42,
	0x41080f0
};

/**
 * @brief Forward arrow pattern for LED matrix
 * 
 * Displays an upward arrow when robot is moving forward
 */
const uint32_t forwardSign[] = {
	0x600f01f,
	0x83fc7fe0,
	0xf00f00f0
};

/**
 * @brief Right arrow pattern for LED matrix
 * 
 * Displays a right-pointing arrow when robot is turning right
 */
const uint32_t rightSign[] = {
	0x2003003,
	0x83fc3fc0,
	0x38030020
};

/**
 * @brief Left arrow pattern for LED matrix
 * 
 * Displays a left-pointing arrow when robot is turning left
 */
const uint32_t leftSign[] = {
	0x400c01c,
	0x3fc3fc1,
	0xc00c0040
};
