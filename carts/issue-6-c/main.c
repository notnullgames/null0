#include "../null0.h"

int main() {
  unsigned int logo = load_image("logo.png");
  Dimensions* before = measure_image(logo);

  unsigned int logo2 = image_scale(logo, 2, 2, FILTER_NEARESTNEIGHBOR);
  Dimensions* after = measure_image(logo2);

  // these should be different
  printf("%u: %dx%d -> %dx%d\n", logo, before->width, before->height, after->width, after->height);
}
