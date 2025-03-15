# Set the remote user and host
REMOTE_USER="jusju"
REMOTE_HOST="softala.haaga-helia.fi"
REMOTE_DIR="/home/jusju"

# Set local storage directory (optional, can be /tmp if you don’t want to keep images)
LOCAL_DIR="/tmp"
mkdir -p "$LOCAL_DIR"

# Loop to take pictures continuously
while true; do
    TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
    IMAGE_FILE="$LOCAL_DIR/image_$TIMESTAMP.jpg"

    # Capture image with timestamp
    fswebcam -d /dev/video0 -i 0 -r 1280x720 --timestamp "%d-%m-%Y %H:%M:%S" --font sans:20 --shadow --no-banner "$IMAGE_FILE"


    # Transfer the image via SCP
    scp "$IMAGE_FILE" "$REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR"

    # Remove local image to save space (optional)
    rm "$IMAGE_FILE"

    # Wait 0.5 seconds (two images per second)
    sleep 0.5
done
