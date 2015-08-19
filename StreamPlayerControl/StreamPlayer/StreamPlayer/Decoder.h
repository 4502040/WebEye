#ifndef FFMPEG_FACADE_DECODER_H
#define FFMPEG_FACADE_DECODER_H

#include <cstdint>
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

#pragma warning( push )
#pragma warning( disable : 4100 )

#include <boost/thread.hpp>

#pragma warning( pop )

namespace FFmpeg
{

#pragma warning( push )
#pragma warning( disable : 4244 )

	extern "C"
	{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
	}

#pragma warning( pop )

	// The FFmpeg framework built using the following configuration:
	// ./configure --toolchain=msvc --enable-gpl --enable-static --disable-shared --disable-ffmpeg
	// --disable-ffplay --disable-ffprobe --disable-ffserver --arch=i386

#pragma comment(lib, "libavformat.a")
#pragma comment(lib, "libavcodec.a")
#pragma comment(lib, "libavdevice.a")
#pragma comment(lib, "libavfilter.a")
#pragma comment(lib, "libavutil.a")
#pragma comment(lib, "libswresample.a")
#pragma comment(lib, "libswscale.a")
#pragma comment(lib, "libpostproc.a")
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "Vfw32.lib")

	namespace Facade
	{
		class Frame;

		/// <summary>
		/// A Decoder class converts a stream into a set of frames. 
		/// </summary>
		class Decoder : private boost::noncopyable
		{
		public:
			/// <summary>
			/// Initializes a new instance of the Frame class.
			/// </summary>
			/// <param name="streamUrl">The url of a stream to decode.</param>
			Decoder(std::string const& streamUrl);

			/// <summary>
			/// Gets the next frame in a stream.
			/// </summary>
			/// <param name="framePtr">The next frame in a stream.</param>
			void GetNextFrame(std::unique_ptr<Frame>& framePtr);

			/// <summary>
			/// Gets an interframe delay, in milliseconds.
			/// </summary>
			int32_t InterframeDelayInMilliseconds() const;

			/// <summary>
			/// Releases all resources used by the decoder.
			/// </summary>
			~Decoder();

		private:

			static std::string AvStrError(int errnum);
						
			AVFormatContext *formatCtxPtr_;
			AVCodecContext  *codecCtxPtr_;			
			int32_t videoStreamIndex_;			
			SwsContext *imageConvertCtxPtr_;
		};
	}
}

#endif // FFMPEG_FACADE_DECODER_H