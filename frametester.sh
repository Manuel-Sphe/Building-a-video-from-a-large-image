#!/bin/bash
# Frame Tester Shell Script
# Brandon Gower-Winter 04/2021

# NOTE: This script requires that you FFMPEG installed.

# Set to 0 if you want to all commands to be printed to terminal
DEBUG=1
if [ $DEBUG -eq 0 ]; then
   set -x
fi

EXE_NAME="extractor"
IMAGE="sloan_image.pgm"

FRAME_SRC="."
# Change this if you want the videos to longer/shorter
FRAME_RATE=24
# Set to 0 if you want to keep the frames
KEEP_FRAMES=1
# Set this to 0 if you want all of the generated mp4 send to their own directory called GENERATED_VIDEOS (Makes it easier to delete them)
VID_DIR=0
# Frame Sequence Names (You can change thee names if you'd like)
SIMPLE="SIMPLE"
BACKWARDS="BACKWARDS"
VERTICAL="VERTICAL"
HORIZONTAL="HORIZONTAL"
REVERSE="REVERSE"
INVERTED="INVERTED"
REVINVERT="REVINVERT"
MULTI="MULTI"
OVER_BOUNDS="OVER_BOUNDS"
NEGATIVE_COORDS="NEGATIVE_COORDS"
ZERO_FRAMES="ZERO_FRAMES"
# These are used in the matery work
THREEPOINT="3POINT"
FIVEPOINT="5POINT"
FIVEPOINT_REV="5POINT_REVERSE"

# Test Cases
# Simple case (gradient=1)
TEST_SIMPLE="./$EXE_NAME $IMAGE -t 0 0 100 100 -s 100 100 -w none $SIMPLE"
TEST_BACKWARDS="./$EXE_NAME $IMAGE -t 100 100 0 0 -s 100 100 -w none $BACKWARDS"
TEST_VERTICAL="./$EXE_NAME $IMAGE -t 0 0 0 100 -s 100 100 -w none $VERTICAL"
TEST_HORIZONTAL="./$EXE_NAME $IMAGE -t 0 0 100 0 -s 100 100 -w none $HORIZONTAL"
TEST_REVERSE="./$EXE_NAME $IMAGE -t 0 0 100 100 -s 100 100 -w reverse $REVERSE"
TEST_INVERT="./$EXE_NAME $IMAGE -t 0 0 100 100 -s 100 100 -w invert $INVERTED"
TEST_REVINVERT="./$EXE_NAME $IMAGE -t 0 0 100 100 -s 100 100 -w revinvert $REVINVERT"
TEST_MULTI="./$EXE_NAME $IMAGE -t 0 0 100 100 -s 100 100 -w none base1 -w reverse base2 -w invert base3 -w revinvert base4"

TEST_OVER="./$EXE_NAME $IMAGE -t 0 1850 0 1950 -s 100 100 -w none $OVER_BOUNDS"
TEST_NEGATIVE="./$EXE_NAME $IMAGE -t -10 -10 100 100 -s 100 100 -w none $NEGATIVE_COORDS"
TEST_ZERO="./$EXE_NAME $IMAGE -t 0 0 100 100 -s 0 0 -w none $ZERO_FRAMES"

TEST_3POINT="./$EXE_NAME $IMAGE -p 0 0 100 100 200 0 -s 100 100 -w none $THREEPOINT"
TEST_5POINT="./$EXE_NAME $IMAGE -p 0 0 100 100 200 0 300 100 400 0 -s 100 100 -w none $FIVEPOINT"
TEST_5POINT_REV="./$EXE_NAME $IMAGE -p 400 0 300 100 200 0 100 100 0 0 -s 100 100 -w none $FIVEPOINT_REV"

#For Mastery Work


# Test functions
create_frame_sequence()
{
   echo -e "\e[1;35m $1 \e[0m"
   # Some very smart people on stackoverflow said this is how you can catch errors
   ERR_VAR=$($1 2>&1)
   if [ $? -eq 0 ]; then
         echo -e "\e[1;32m Success: \e[0m Building video sequence."
         mkdir $2
         # Move all of the frames to their own folder (This does assume the student is writing all of the images to the working directory)
         # Change FRAME_SRC if they write it to another folder (like ./bin/ or ./out/)
         find "$FRAME_SRC" -name "*.pgm" ! -name "$IMAGE" -exec mv -t "$2" {} +
         num_frames=$(find ./$2/ -name "*.pgm" | wc -l)
         col="\e[1;32m"
         if [ $num_frames -ne $3 ]; then
            col="\e[1;33m"
         fi
         echo -e "$col $num_frames \e[0m Frames Generated."
         echo
         # Using these commands to account for the cases where students didn't follow the 'padded' frame naming (ie: 000, 001)
         # It does still assume that the frames have some sort of numerical ordering to them (0, 1, 2 ...) but a student does not deserve full marks if they did
         # not follow the sequence numbering mentioned in the assignment brief.
         # The assignment brief also started the sequence at 000 whereas ffmpeg starts its sequences at 001
         # If you are generating over 99 999 images, you'll need to increase the '5' to '6' or higher
         count=1
         for file in $(find ./$2/ -name "*.pgm" | sort -V); do
            mv $file "$2/$(printf %05d $count).pgm"
            ((count++))
         done
         echo "ffmpeg -y -framerate $FRAME_RATE -i $2/%05d.pgm -pix_fmt rgb24 -vcodec png $2.mp4"
         ffmpeg -y -framerate $FRAME_RATE -i "$2/%05d.pgm" -pix_fmt rgb24 -vcodec png $2.mp4

         if [ $KEEP_FRAMES -eq 1 ]; then
            rm -rf $2
         fi

   else
         echo -e "\e[1;31m Error: \e[0m $ERR_VAR"
   fi
}

echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Frame Tester <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
echo "Working Directory:"
pwd
echo "Executable Name: $EXE_NAME"
echo
echo "Attempting Simple Test Case"
create_frame_sequence "$TEST_SIMPLE" $SIMPLE 100
create_frame_sequence "$TEST_BACKWARDS" $BACKWARDS 100
create_frame_sequence "$TEST_VERTICAL" $VERTICAL 100
create_frame_sequence "$TEST_HORIZONTAL" $HORIZONTAL 100
create_frame_sequence "$TEST_REVERSE" $REVERSE 100
create_frame_sequence "$TEST_INVERT" $INVERTED 100
create_frame_sequence "$TEST_REVINVERT" $REVINVERT 100
create_frame_sequence "$TEST_MULTI" $MULTI 400
echo
echo -e "\e[1;31m  Some of these tests might fail! \e[0m"
echo
create_frame_sequence "$TEST_OVER" $OVER_BOUNDS 100
create_frame_sequence "$TEST_NEGATIVE" $NEGATIVE_COORDS 110
create_frame_sequence "$TEST_ZERO" $ZERO_FRAMES 100

#Uncomment the following if you want to test the mastery work
#echo ">>>>>>>>>>>>>>>>>>>>\e[1;31m Testing Mastery Work \e[0m<<<<<<<<<<<<<<<<<<<<<<<"
#create_frame_sequence "$TEST_3POINT" $THREEPOINT 200
#create_frame_sequence "$TEST_5POINT" $FIVEPOINT 400
#create_frame_sequence "$TEST_5POINT_REV" $FIVEPOINT_REV 400


if [ $VID_DIR -eq 0 ]; then
   mkdir GENERATED_VIDEOS
   mv *.mp4 GENERATED_VIDEOS
fi