#pragma once

#include <opencv2/core.hpp>
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/c/c_api.h"

using namespace cv;

struct DetectResult {
	int label = -1;
	float score = 0;
	float ymin = 0.0;
	float xmin = 0.0;
	float ymax = 0.0;
	float xmax = 0.0;
};

class ObjectDetector {
public:
	ObjectDetector(const char* modelBuffer, int size, bool quantized = false);
	~ObjectDetector();
	DetectResult* detect(Mat src);
	const int DETECT_NUM = 5;
private:
	// members
	const int DETECTION_MODEL_SIZE = 640;
	const int DETECTION_MODEL_CNLS = 3;
	bool m_modelQuantized = false;
	char* m_modelBytes = nullptr;
	TfLiteModel* m_model;
	TfLiteInterpreter* m_interpreter;
	TfLiteTensor* m_input_tensor = nullptr;
	const TfLiteTensor* m_output_locations = nullptr;
	const TfLiteTensor* m_output_classes = nullptr;
	const TfLiteTensor* m_output_scores = nullptr;
	const TfLiteTensor* m_num_detections = nullptr;

	// Methods
	void initDetectionModel(const char* modelBuffer, int size);
};
