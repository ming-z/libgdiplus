#include <assert.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if !defined(_WIN32)
#include <unistd.h>
#endif

BOOL floatsEqual (float v1, float v2)
{
    if (isnan (v1))
        return isnan (v2);

    if (isinf (v1))
        return isinf (v2);

    return fabs (v1 - v2) < 0.0001;
}

void verifyMatrix (GpMatrix *matrix, REAL e1, REAL e2, REAL e3, REAL e4, REAL e5, REAL e6)
{
    float elements[6];
    GdipGetMatrixElements (matrix, elements);

    if (!floatsEqual (elements[0], e1) ||
        !floatsEqual (elements[1], e2) ||
        !floatsEqual (elements[2], e3) ||
        !floatsEqual (elements[3], e4) ||
        !floatsEqual (elements[4], e5) ||
        !floatsEqual (elements[5], e6)) {

        fprintf (stderr, "Expected matrices to be equal\n");
        fprintf (stderr, "Expected: %f, %f, %f, %f, %f, %f\n", e1, e2, e3, e4, e5, e6);
        fprintf (stderr, "Actual:   %f, %f, %f, %f, %f, %f\n\n", elements[0], elements[1], elements[2], elements[3], elements[4], elements[5]);

        abort ();
    }
}

#if !defined(USE_WINDOWS_GDIPLUS)
#define createWchar(c) g_utf8_to_utf16 (c, -1, NULL, NULL, NULL);
#define freeWchar(c) g_free(c)
#define wcharFromChar(c) createWchar(c)
#else
WCHAR* wcharFromChar(const char *c)
{
    size_t length = strlen (c);

    WCHAR *wc = (WCHAR *)malloc((length + 1) * sizeof(WCHAR *));
    swprintf (wc, length + 1, L"%hs", c);
    wc[length] = 0;

    return wc;
}

#define createWchar(c) L ##c
#define freeWchar(c)
#endif

#define assertEqualInt(actual, expected)                   \
{                                                          \
    if ((int)actual != (int)expected)                      \
    {                                                      \
        fprintf (stderr, "Expected: %d\n", (int)expected); \
        fprintf (stderr, "Actual:   %d\n", (int)actual);   \
        assert ((int)actual == (int)expected);             \
    }                                                      \
}

#define assertEqualFloat(actual, expected)                   \
{                                                            \
    if (!floatsEqual ((float)actual, (float)expected))       \
    {                                                        \
        fprintf (stderr, "Expected: %f\n", (float)expected); \
        fprintf (stderr, "Actual:   %f\n", (float)actual);   \
        assert ((float)actual == (float)expected);           \
    }                                                        \
}

CLSID bmpEncoderClsid = { 0x557cf400, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID tifEncoderClsid = { 0x557cf405, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID gifEncoderClsid = { 0x557cf402, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID pngEncoderClsid = { 0x557cf406, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID jpegEncoderClsid = { 0x557cf401, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID icoEncoderClsid = { 0x557cf407, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID wmfEncoderClsid = { 0x557cf404, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };
CLSID emfEncoderClsid = { 0x557cf403, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x0, 0x0, 0xf8, 0x1e, 0xf3, 0x2e } };

#if defined(USE_WINDOWS_GDIPLUS)
GUID memoryBmpRawFormat = {0xb96b3caaU, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
#endif
GUID bmpRawFormat = {0xb96b3cabU, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID tifRawFormat = {0xb96b3cb1U, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID gifRawFormat = {0xb96b3cb0U, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID pngRawFormat = {0xb96b3cafU, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID jpegRawFormat = {0xb96b3caeU, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID icoRawFormat = {0xb96b3cb5U, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID wmfRawFormat = {0xb96b3cadU, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};
GUID emfRawFormat = {0xb96b3cacU, 0x0728U, 0x11d3U, {0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e}};

BOOL is_32bit ()
{
    return sizeof(int *) == 4;
}

#if defined(USE_WINDOWS_GDIPLUS)
#define WINDOWS_GDIPLUS 1
#else
#define WINDOWS_GDIPLUS 0
#endif

#define verifyBitmap(image, expectedRawFormat, expectedPixelFormat, expectedWidth, expectedHeight, expectedFlags, expectedPropertyCount, checkFlags) \
    verifyImage(image, ImageTypeBitmap, expectedRawFormat, expectedPixelFormat, 0, 0, expectedWidth, expectedHeight, (REAL)expectedWidth, (REAL)expectedHeight, expectedFlags, expectedPropertyCount, checkFlags)

#define verifyMetafile(image, expectedRawFormat, expectedX, expectedY, expectedWidth, expectedHeight, expectedDimensionWidth, expectedDimensionHeight) \
    verifyImage(image, ImageTypeMetafile, expectedRawFormat, PixelFormat32bppRGB, expectedX, expectedY, expectedWidth, expectedHeight, expectedDimensionWidth, expectedDimensionHeight, 327683, 0, TRUE)

#define verifyImage(image, expectedType, expectedRawFormat, expectedPixelFormat, expectedX, expectedY, expectedWidth, expectedHeight, expectedDimensionWidth, expectedDimensionHeight, expectedFlags, expectedPropertyCount, checkFlags) \
{ \
    GpStatus status; \
    ImageType type; \
    GUID rawFormat; \
    PixelFormat pixelFormat; \
    UINT width; \
    UINT height; \
    GpRectF bounds; \
    GpUnit unit; \
    REAL dimensionWidth; \
    REAL dimensionHeight; \
    UINT flags; \
    UINT propertyCount; \
 \
    status = GdipGetImageType (image, &type); \
    assertEqualInt (status, Ok); \
    assertEqualInt (type, expectedType); \
 \
    status = GdipGetImageRawFormat (image, &rawFormat); \
    assertEqualInt (status, Ok); \
    assert (memcmp ((void *) &rawFormat, (void *) &expectedRawFormat, sizeof (GUID)) == 0); \
 \
    status = GdipGetImagePixelFormat (image, &pixelFormat); \
    assertEqualInt (status, Ok); \
    assertEqualInt (pixelFormat, expectedPixelFormat); \
 \
    status = GdipGetImageWidth (image, &width); \
    assertEqualInt (status, Ok); \
    assertEqualInt (width, expectedWidth); \
 \
    status = GdipGetImageHeight (image, &height); \
    assertEqualInt (status, Ok); \
    assertEqualInt (height, expectedHeight); \
 \
    status = GdipGetImageBounds (image, &bounds, &unit); \
    assertEqualInt (status, Ok); \
    assertEqualFloat (bounds.X, expectedX); \
    assertEqualFloat (bounds.Y, expectedY); \
    assertEqualFloat (bounds.Width, (REAL)expectedWidth); \
    assertEqualFloat (bounds.Height, (REAL)expectedHeight); \
    assertEqualInt (unit, UnitPixel); \
 \
    /* Libgdiplus and GDI+ have different exact degrees of accuracy. */ \
    /* Typically they differ by +-0.02. */ \
    /* This is an acceptable difference. */ \
    status = GdipGetImageDimension (image, &dimensionWidth, &dimensionHeight); \
    assertEqualInt (status, Ok); \
    assert (fabsf (dimensionWidth - expectedDimensionWidth) <= 0.05); \
    assert (fabsf (dimensionHeight - expectedDimensionHeight) <= 0.05); \
 \
    /* FIXME: libgdiplus and GDI+ have different results for bitmap images. */ \
    if (checkFlags || WINDOWS_GDIPLUS) \
    { \
        status = GdipGetImageFlags (image, &flags); \
        assertEqualInt (status, Ok); \
        assertEqualInt (flags, (expectedFlags)); \
    } \
 \
    status = GdipGetPropertyCount (image, &propertyCount); \
    assertEqualInt (status, Ok); \
    /* FIXME: libgdiplus returns 0 for each image. */ \
	if (WINDOWS_GDIPLUS) \
	{ \
		assertEqualInt (propertyCount, expectedPropertyCount); \
	} \
}

#define HEX__(n) 0x##n##LU
#define B8__(x) ((x&0x0000000FLU)?1:0) \
+ ((x&0x000000F0LU)?2:0)               \
+ ((x&0x00000F00LU)?4:0)               \
+ ((x&0x0000F000LU)?8:0)               \
+ ((x&0x000F0000LU)?16:0)              \
+ ((x&0x00F00000LU)?32:0)              \
+ ((x&0x0F000000LU)?64:0)              \
+ ((x&0xF0000000LU)?128:0)

#define B8(d) ((BYTE)B8__(HEX__(d)))

// A utility for dumping byte arrays to the console for debugging purposes.
void dumpBytes (BYTE *bytes, int length)
{
    printf("%u\n", length);
    for (int i = 0; i < length; i++) {
        printf("0x%02x", bytes[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }

    printf("\n\n");
}

void deleteFile (const char *file)
{
#if !defined(_WIN32)
    unlink (file);
#else
    DeleteFileA (file);
#endif
}
