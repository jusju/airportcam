#!/bin/bash

# Directories
IMG_DIR="/home/jusju"
WEBPAGE="/var/www/html/kuvat/kuvanaytin.html"
TMP_DIR="/home/jusju/tmp"  # Temporary directory for processed images

# Ensure directories exist
mkdir -p "$(dirname "$WEBPAGE")"
mkdir -p "$TMP_DIR"

# Get the 120 most recent .jpg images sorted from oldest to newest
IMAGES=($(find "$IMG_DIR" -type f -name "*.jpg" -printf '%T+ %p\n' | sort | tail -n 120))

# Loop through images and display each one for 1 second
for IMAGE in "${IMAGES[@]}"; do
    if [[ -f "$IMAGE" ]]; then
        # Extract timestamp from file metadata
        TIMESTAMP=$(date -r "$IMAGE" '+%d.%m.%Y %H:%M:%S')

        # Generate a temporary image with timestamp
        TMP_IMAGE="$TMP_DIR/$(basename "$IMAGE")"
        convert "$IMAGE" -gravity south -pointsize 30 -fill white -annotate +0+20 "$TIMESTAMP" "$TMP_IMAGE"

        # Update the webpage with the new image
        echo "<html><head><meta http-equiv='refresh' content='1'></head><body><img src='/kuvat/$(basename "$TMP_IMAGE")' style='width:50%;height:auto;'></body></html>" > "$WEBPAGE"

        # Move the processed image to the web directory
        mv "$TMP_IMAGE" /var/www/html/kuvat/

        # Wait 1 second before showing the next image
        sleep 0.5
    fi
done

# Clean up: delete original images and temporary images after display
# Clean up: delete only images older than 5 minutes
find "$IMG_DIR" -type f -name "*.jpg" -mmin +5 -delete
find /var/www/html/kuvat/ -type f -name "*.jpg" -mmin +5 -delete

# rm -f "${IMAGES[@]}"
# rm -f /var/www/html/kuvat/*.jpg

# Remove the HTML file to keep the directory clean
#rm -f "$WEBPAGE"

