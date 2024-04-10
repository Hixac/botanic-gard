#include <nfd.hpp>

namespace Utils {
	
	class FileDialog
	{
	public:
		enum Error { None, FileDidntOpened };
		
		struct Path {
		    nfdu8char_t* out;
			Error err;
		};
		
		inline static FileDialog& Get() { static FileDialog dlg; return dlg; }

		Path Open(nfdfilteritem_t filterItem = { "Photo", "jpg,png" });

	private:
		FileDialog();
		
	    NFD::Guard ms_guard;
		
	};
	
}
