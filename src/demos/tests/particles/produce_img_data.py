import cv2
import numpy as np

if __name__ == "__main__":
    
    # img_file_name = "rb.jpg"
    # nm = img_file_name.replace(".jpg", "")

    img_file_name = "S.png"
    nm = img_file_name.replace(".png", "")

    img = cv2.imread('src/demos/tests/particles/' + img_file_name)
    # img_resized = cv2.resize(img, None, fx=0.5, fy=0.5)
    image_to_use = img

    img_width = image_to_use.shape[1]
    img_height = image_to_use.shape[0]

    new_img = np.transpose(image_to_use, (2, 0, 1))
    # new_img[0] = np.flipud(new_img[0])
    # new_img[1] = np.flipud(new_img[1])
    # new_img[2] = np.flipud(new_img[2])

    with open("src/demos/tests/particles/img.bin", "wb") as new_file:

        full_byte_array = bytearray(np.uint16(img_width).tobytes()) + \
                bytearray(np.uint16(img_height).tobytes()) + \
                bytearray(new_img)
        new_file.write(full_byte_array)