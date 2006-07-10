// flvinfo.c

// A small program that displayis video info of an flv video using libavcodec
//
// http://www.inb.uni-luebeck.de/~boehme/using_libavcodec.html webpage was very
// useful to kick in implementation of this program.
//
// Use
// gcc -o flvinfo flvinfo.c -lavformat  -I/usr/include/ffmpeg
//
// to build (assuming libavformat is correctly installed on your system).
//
// Run using
// ./flvinfo myvideofile.flv
//

#include <avcodec.h>
#include <avformat.h>

#include <stdio.h>

void dump_streams(AVFormatContext *ic, int index, const char *url, int is_output)
{
int i;
AVCodecContext *enc;
AVCodec *p;

    for (i = 0; i < ic->nb_streams; i++) {
        AVStream *st = ic->streams[i];
		enc = st->codec;
		p = avcodec_find_decoder(enc->codec_id);
		if (p == NULL) {
			fprintf(stderr, "Unknown codec %d of %d!\n", enc->codec_id, enc->codec_type);
			continue;
		}

		switch(enc->codec_type) {
		case CODEC_TYPE_VIDEO:
			printf("%s: codec=%s", url, p->name);
			if (enc->width) {
				printf(" width=%d", enc->width);
			}
			if (enc->height) {
				printf(" height=%d", enc->height);
			}
			printf("\n", enc->height);
		}
    }

}

int main(int argc, char *argv[])
{

AVFormatContext *pFormatCtx;
char *file;
int i;

	if (argc < 2) {
		return -1; // no file specified
	}

    // Register all formats and codecs
    av_register_all();

	for (i = 1; i < argc; i++) {
		// Open video file
		if (av_open_input_file(&pFormatCtx, argv[i], NULL, 0, NULL) != 0) {
			return -1; // Couldn't open file
		}

		// Retrieve stream information
		if (av_find_stream_info(pFormatCtx) < 0) {
			return -1; // Couldn't find stream information
		}

		// Dump information about file onto standard error
		dump_streams(pFormatCtx, 0, argv[i], 0);

		// Close the video file
		av_close_input_file(pFormatCtx);
	}

    return 0;
}
