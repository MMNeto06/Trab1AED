// imageRGBTest - A program that performs some operations on RGB images.
//
// This program is an example use of the imageRGB module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// The AED Team <jmadeira@ua.pt, jmr@ua.pt, ...>
// 2025

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "imageRGB.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  program_name = argv[0];
  if (argc != 1) {
    error(1, 0, "Usage: imageRGBTest");
  }

  ImageInit();

  // Creating and displaying some images

  printf("1) ImageCreate\n");
  Image white_image = ImageCreate(100, 100);
  // ImageRAWPrint(white_image);

  printf("2) ImageCreateChess(black)+ ImageSavePBM\n");
  Image image_chess_1 = ImageCreateChess(150, 120, 30, 0x000000);  // black
  // ImageRAWPrint(image_chess_1);
  ImageSavePBM(image_chess_1, "chess_image_1.pbm");

  printf("3) ImageCreateChess(red) + ImageSavePPM\n");
  Image image_chess_2 = ImageCreateChess(20, 20, 8, 0xff0000);  // red
  ImageRAWPrint(image_chess_2);
  ImageSavePPM(image_chess_2, "chess_image_2.ppm");

  printf("4) ImageCreateChess(all black)\n");
  Image black_image = ImageCreateChess(100, 100, 100, 0x000000);  // all black
  // ImageRAWPrint(black_image);
  ImageSavePBM(black_image, "black_image.pbm");

  printf("5) ImageCopy\n");
  Image copy_image = ImageCopy(image_chess_1);
  // ImageRAWPrint(copy_image);
  if (copy_image != NULL) {
    ImageSavePBM(copy_image, "copy_image.pbm");
  }

  printf("6) ImageLoadPBM\n");
  Image image_1 = ImageLoadPBM("img/feep.pbm");
  ImageRAWPrint(image_1);

  printf("7) ImageLoadPPM\n");
  Image image_2 = ImageLoadPPM("img/feep.ppm");
  ImageRAWPrint(image_2);

  printf("8) ImageCreatePalete\n");
  Image image_3 = ImageCreatePalete(4 * 32, 4 * 32, 4);
  ImageSavePPM(image_3, "palete.ppm");

  printf("9) ImageIsEqual\n");
  assert(ImageIsEqual(image_chess_1, copy_image));
  printf("image_chess_1 and copy_image are the same -> passed\n");
  assert(ImageIsDifferent(image_chess_2, copy_image));
  printf("image_chess_2 and copy_image are not the same -> passed\n");
  Image image_chess_1_blue = ImageCreateChess(150, 120, 30, 0x0000ff);
  ImageSavePPM(image_chess_1_blue, "chess_image_1_blue.ppm");
  assert(ImageIsDifferent(image_chess_1, image_chess_1_blue));
  printf("image_chess_2 and copy_image are not the same -> passed\n");

  printf("11) ImageRotate90CW\n");
  Image rotate90_original = ImageCreateChess(100, 60, 27, 0x00f1f3);
  Image rotate90_test = ImageRotate90CW(rotate90_original);
  ImageSavePPM(rotate90_original, "original90_test.ppm");
  ImageSavePPM(rotate90_test, "rotate90_test.ppm");

  printf("12) ImageRotate180CW\n");
  Image rotate180_original = ImageCreateChess(100, 60, 27, 0x00f1f3);
  Image rotate180_test = ImageRotate180CW(rotate180_original);
  ImageSavePPM(rotate180_original, "original180_test.ppm");
  ImageSavePPM(rotate180_test, "rotate180_test.ppm");
  
  printf("13) ImageRegionFillingRecursive\n");
  Image recursive_test = ImageCreateChess(300, 300, 30, 0x00f1ff);
  printf("Recolored %d pixels\n",ImageRegionFillingRecursive(recursive_test, 75, 15, 0));
  ImageSavePPM(recursive_test, "recursive_test.ppm");
  
  printf("14) ImageRegionFillingWithSTACK\n");
  Image stack_test = ImageCreateChess(300, 300, 30, 0x00f1ff);
  printf("Recolored %d pixels\n",ImageRegionFillingWithSTACK(stack_test, 75, 15, 0));
  ImageSavePPM(stack_test, "stack_test.ppm");

  printf("15) ImageRegionFillingWithQUEUE\n");
  Image queue_test = ImageCreateChess(300, 300, 30, 0x00f1ff);
  printf("Recolored %d pixels\n",ImageRegionFillingWithSTACK(queue_test, 75, 15, 0));
  ImageSavePPM(queue_test, "stack_test.ppm");

  printf("16) ImageSegmentation with ImageRegionFillingRecursive\n");
  ImageSegmentation(recursive_test, ImageRegionFillingRecursive);
  ImageSavePPM(recursive_test, "segmentation_recursive_test.ppm");

  printf("17) ImageSegmentation with ImageRegionFillingWithSTACK\n");
  ImageSegmentation(stack_test, ImageRegionFillingRecursive);
  ImageSavePPM(stack_test, "segmentation_stack_test.ppm");

  printf("18) ImageSegmentation with ImageRegionFillingWithQUEUE\n");
  ImageSegmentation(queue_test, ImageRegionFillingRecursive);
  ImageSavePPM(queue_test, "segmentation_queue_test.ppm");

  ImageDestroy(&white_image);
  ImageDestroy(&black_image);
  if (copy_image != NULL) {
    ImageDestroy(&copy_image);
  }
  ImageDestroy(&image_chess_1);
  ImageDestroy(&image_chess_2);
  ImageDestroy(&image_1);
  ImageDestroy(&image_2);
  ImageDestroy(&image_3);
  ImageDestroy(&image_chess_1_blue);
  ImageDestroy(&recursive_test);

  return 0;
}
