#include "filters.hpp"

using namespace std;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened()) // check if we succeeded
        return -1;

    namedWindow("Filtered", WINDOW_AUTOSIZE);
    cap.set(CV_CAP_PROP_FPS, 60);

    Mat frame;
    FilterProcessor bordaProcessor;
	FilterProcessor backProcessor;
    bordaProcessor.addFilter(detectarBordas);
    backProcessor.addFilter(borrarFundo);

    PipelineProcessor pipeline;
    pipeline.addFilterProcessor(&bordaProcessor);
    pipeline.addFilterProcessor(&backProcessor);

    while(true) {
        cap >> frame;
        frame.copyTo(bordaProcessor.image);
        frame.copyTo(backProcessor.image);
        pipeline.process();
        imshow("Filtered", pipeline.join());
        imshow("borda", bordaProcessor.image);
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}
