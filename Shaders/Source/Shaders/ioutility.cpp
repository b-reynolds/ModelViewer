#define _CRT_SECURE_NO_WARNINGS
#include "ioutility.h"

/**
 * \brief Open a file and copy the contents into the output variable
 * \param filePath File path
 * \param out Output variable
 * \return True if file was read successfully
 */
char* IOUtility::readFile(const char* filePath)
{
	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (filePath != NULL) {
		fp = fopen(filePath, "rt");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
