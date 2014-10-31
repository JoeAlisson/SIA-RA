#include "filters.hpp"

using namespace std;

int main(int, char**)
{
    VideoCapture cap(0);
    if (!cap.isOpened())
        return -1;

    namedWindow("Filtered", WINDOW_AUTOSIZE);
    cap.set(CV_CAP_PROP_FPS, 60);

    Mat frame;
    FilterProcessor bordaProcessor;
	FilterProcessor backProcessor;

    //bordaProcessor.addFilter(edgeDetectSobel);
    //backProcessor.addFilter(Gaussian);
    bordaProcessor.addFilter(edgeDetectCanny);

    //bordaProcessor.addFilter(edgeDetectLaplacian);
    backProcessor.addFilter(GaussianSatured);
    //backProcessor.addFilter(bilateralSatured);


    PipelineProcessor pipeline;
    pipeline.addFilterProcessor(&bordaProcessor);
    pipeline.addFilterProcessor(&backProcessor);

    while(true) {
        cap >> frame;
        imshow("original", frame);
        pipeline.setImage(frame);
        pipeline.process();
        imshow("Filtered", pipeline.join());
        imshow("borda", bordaProcessor.getImage());
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}
