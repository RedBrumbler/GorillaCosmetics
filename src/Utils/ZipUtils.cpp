#include "Utils/ZipUtils.hpp"
#include "zip/shared/zip.h"
#include "beatsaber-hook/shared/utils/utils-functions.h"
#include "logging.hpp"
#include "Utils/FileUtils.hpp"
#include <fstream>
namespace ZipUtils
{
    void Unzip(std::string src, std::string dst)
    {
        if (direxists(dst))
        { 
            INFO("Directory %s already existed, returning!", dst.c_str());
            return;
        }

        INFO("Unzipping file from %s to %s", src.c_str(), dst.c_str());
        FileUtils::mkdir(dst);

        //Open the ZIP archive
        int err = 0;
        zip *z = zip_open(src.c_str(), 0, &err);
        int fileCount = zip_get_num_files(z);
        // we want to unzip each file
        for (int i = 0; i < fileCount; i++)
        {
            // stat datatype
            struct zip_stat st;
            zip_stat_init(&st);

            // get file @ index
            zip_stat_index(z, i, 0, &st);
            INFO("\t Found %s", st.name);

            //Alloc memory for its uncompressed contents
            char *contents = new char[st.size];

            //Read the compressed file
            zip_file *f = zip_fopen_index(z, i, 0);
            zip_fread(f, contents, st.size);

            
            // write file to dst as filename
            std::string filedst = dst + st.name;
            std::ofstream outfile (filedst, std::ofstream::binary);
            outfile.write(contents, st.size);            

            zip_fclose(f);
            delete[] contents;            
        }
        INFO("Done Unzipping");
        //And close the archive
        zip_close(z);
    }
}