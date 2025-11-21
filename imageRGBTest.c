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
#include <time.h>

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

  //usado para a análise experimental
  /*printf("9.1) ImageIsEqual Análise experimental\n");
  Image imgW = ImageLoadPPM("imgEquals/img1pxW.ppm");
  Image imgB = ImageLoadPPM("imgEquals/img1pxB.ppm");
  printf("Size = 1px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();
  
  imgW = ImageLoadPPM("imgEquals/img2pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img2pxB.ppm");
  printf("Size = 2px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img4pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img4pxB.ppm");
  printf("Size = 4px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img8pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img8pxB.ppm");
  printf("Size = 8px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img16pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img16pxB.ppm");
  printf("Size = 16px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img32pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img32pxB.ppm");
  printf("Size = 32px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img64pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img64pxB.ppm");
  printf("Size = 64px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img100pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img100pxB.ppm");
  printf("Size = 100px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img500pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img500pxB.ppm");
  printf("Size = 500px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img1000pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img1000pxB.ppm");
  printf("Size = 1000px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img5000pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img5000pxB.ppm");
  printf("Size = 5000px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img10000pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img10000pxB.ppm");
  printf("Size = 10000px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img100000pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img100000pxB.ppm");
  printf("Size = 100000px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();

  imgW = ImageLoadPPM("imgEquals/img1000000pxW.ppm");
  imgB = ImageLoadPPM("imgEquals/img1000000pxB.ppm");
  printf("Size = 1000000px - \n");
  InstrReset();
  assert(ImageIsDifferent(imgW, imgB));
  InstrPrint();
  
  ImageDestroy(&imgW);
  ImageDestroy(&imgB);*/

  //usado para a análise experimental
  /*printf("9.2) ImageIsEqual Análise tempos adicional\n");
  printf("Best Case != - Imagens com alturas diferentes\n");
  InstrReset();
  assert(!ImageIsEqual(copy_image, image_chess_2));
  InstrPrint();

  printf("Best case == - Mesma imagem passada\n");
  InstrReset();
  assert(ImageIsEqual(white_image, white_image));
  InstrPrint();*/

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
  clock_t start = clock();
  printf("Recolored %d pixels\n",ImageRegionFillingRecursive(recursive_test, 75, 15, 0));
  clock_t end = clock();
  ImageSavePPM(recursive_test, "recursive_test.ppm"); 
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Tempo: %f segundos\n", elapsed);
  
  printf("14) ImageRegionFillingWithSTACK\n");
  Image stack_test = ImageCreateChess(300, 300, 30, 0x00f1ff);
  start = clock();
  printf("Recolored %d pixels\n",ImageRegionFillingWithSTACK(stack_test, 75, 15, 0));
  end = clock();
  ImageSavePPM(stack_test, "stack_test.ppm");
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Tempo: %f segundos\n", elapsed);

  printf("15) ImageRegionFillingWithQUEUE\n");
  Image queue_test = ImageCreateChess(300, 300, 30, 0x00f1ff);
  start = clock();
  printf("Recolored %d pixels\n",ImageRegionFillingWithQUEUE(queue_test, 75, 15, 0));
  end = clock();
  ImageSavePPM(queue_test, "queue_test.ppm");
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Tempo: %f segundos\n", elapsed);

  printf("16) ImageRegionFillingWithQUEUE Big Image\n");
  Image queue_test_big = ImageCreateChess(3000, 3000, 3000, 0x00f1ff);
  start = clock();
  printf("Recolored %d pixels\n",ImageRegionFillingWithQUEUE(queue_test_big, 75, 15, 0));
  end = clock();
  ImageSavePPM(queue_test_big, "queue_test_big.ppm");
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Tempo: %f segundos\n", elapsed);

  printf("17) ImageRegionFillingWithSTACK Big Image\n");
  Image stack_test_big = ImageCreateChess(3000, 3000, 3000, 0x00f1ff);
  ImageSavePPM(stack_test_big, "big_original.ppm");
  start = clock();
  printf("Recolored %d pixels\n",ImageRegionFillingWithSTACK(stack_test_big, 75, 15, 0));
  end = clock();
  ImageSavePPM(stack_test_big, "stack_test_big.ppm");
  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Tempo: %f segundos\n", elapsed);

  printf("18) ImageSegmentation with ImageRegionFillingRecursive\n");
  printf("Regions: %d\n", ImageSegmentation(recursive_test, ImageRegionFillingRecursive));
  ImageSavePPM(recursive_test, "segmentation_recursive_test.ppm");

  printf("19) ImageSegmentation with ImageRegionFillingWithSTACK\n");
  printf("Regions: %d\n", ImageSegmentation(stack_test, ImageRegionFillingWithSTACK));
  ImageSavePPM(stack_test, "segmentation_stack_test.ppm");

  printf("20) ImageSegmentation with ImageRegionFillingWithQUEUE\n");
  printf("Regions: %d\n", ImageSegmentation(queue_test, ImageRegionFillingWithQUEUE));
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
  ImageDestroy(&rotate90_original);
  ImageDestroy(&rotate90_test);
  ImageDestroy(&rotate180_original);
  ImageDestroy(&rotate180_test);

  ImageDestroy(&stack_test);
  ImageDestroy(&queue_test);
  ImageDestroy(&queue_test_big);
  ImageDestroy(&stack_test_big);


  return 0;
}
