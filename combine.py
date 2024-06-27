from PIL import Image
import numpy as np

def read_ppm_p3(filename):
    with open(filename, 'r') as f:
        header = f.readline().strip()
        if header != 'P3':
            raise ValueError('Not a PPM P3 file')
        dimensions = f.readline().strip().split()
        width, height = int(dimensions[0]), int(dimensions[1])
        maxval = int(f.readline().strip())
        if maxval != 255:
            raise ValueError('Only maxval 255 supported')
        data = f.read().split()
        img_data = np.array(data, dtype=np.uint8).reshape((height, width, 3))
        return img_data

def write_ppm_p3(filename, img_data):
    height, width, _ = img_data.shape
    with open(filename, 'w') as f:
        f.write('P3\n')
        f.write(f'{width} {height}\n')
        f.write('255\n')
        for row in img_data:
            for pixel in row:
                f.write(f'{pixel[0]} {pixel[1]} {pixel[2]} ')
            f.write('\n')

def slice_and_combine(filenames, output_filename):
    images = [read_ppm_p3(fn) for fn in filenames]
    height, width, _ = images[0].shape
    slice_width = width // len(images)
    
    combined_image = np.hstack([img[:, i*slice_width:(i+1)*slice_width] for i, img in enumerate(images)])
    
    write_ppm_p3(output_filename, combined_image)

# File names for the input PPM files
input_filenames = [f'image_{i}.ppm' for i in {9,7,5,3,1}]
# Output PPM file name
output_filename = 'combined_image.ppm'

# Slice and combine the PPM files
slice_and_combine(input_filenames, output_filename)

# Convert the combined PPM file to PNG
combined_img = Image.open(output_filename)
combined_img.save('combined_image.png')

# Optionally open the image
combined_img.show()

