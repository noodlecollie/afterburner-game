#include <cstring>
#include "NightfireToXashModelConverter.h"
#include "elements/Conversions.h"

namespace NFMDL
{
	template<typename T>
	static inline void CopyElementArray(const ElementArray<T>& src, ElementArray<T>& dest)
	{
		dest.AllocateAndZero(src.Count());

		src.ForEach([&dest](uint32_t index, const T& element)
		{
			dest[index] = element;
		});
	}

	template<typename TS, typename TD>
	static inline void CopyElementArray(const ElementArray<TS>& src, ElementArray<TD>& dest)
	{
		dest.AllocateAndZero(src.Count());

		src.ForEach([&dest](uint32_t index, const TS& element)
		{
			Convert(element, dest[index]);
		});
	}

	std::string NightfireToXashModelConverter::GetConversionError() const
	{
		return m_ConversionError;
	}

	void NightfireToXashModelConverter::SetInputFile(const std::shared_ptr<const NightfireModelFile>& inFile)
	{
		m_InModelFile = inFile;
	}

	void NightfireToXashModelConverter::SetOutputFile(const std::shared_ptr<XashModelFile>& outFile)
	{
		m_OutModelFile = outFile;
	}

	bool NightfireToXashModelConverter::Convert()
	{
		m_ConversionError.clear();

		if ( !m_InModelFile )
		{
			m_ConversionError = "No input model was provided.";
			return false;
		}

		if ( !m_OutModelFile )
		{
			m_ConversionError = "No output model was provided.";
			return false;
		}

		bool success = false;

		try
		{
			ConvertInternal();
		}
		catch ( const std::exception& ex )
		{
			m_ConversionError = ex.what();
		}

		return success;
	}

	void NightfireToXashModelConverter::ConvertInternal()
	{
		NFMDL::Convert(m_InModelFile->Header, m_OutModelFile->Header);

		CopyElementArray(m_InModelFile->Bones, m_OutModelFile->Bones);
		CopyElementArray(m_InModelFile->BoneControllers, m_OutModelFile->BoneControllers);
		CopyElementArray(m_InModelFile->HitBoxes, m_OutModelFile->HitBoxes);
		CopyElementArray(m_InModelFile->Sequences, m_OutModelFile->Sequences);
		CopyElementArray(m_InModelFile->SequenceGroups, m_OutModelFile->SequenceGroups);
		CopyElementArray(m_InModelFile->Attachments, m_OutModelFile->Attachments);

		m_OutModelFile->Skins = m_InModelFile->Skins;
		m_OutModelFile->Events = m_InModelFile->Events;
		m_OutModelFile->FootPivots = m_InModelFile->FootPivots;
		m_OutModelFile->AnimationData = m_InModelFile->AnimationData;

		ConstructHLBodyGroups();

		// TODO: The rest
	}

	void NightfireToXashModelConverter::ConstructHLBodyGroups()
	{
		/*
			The process of this is as follows:

			Nightfire and Half Life body groups are equivalent. However, for the sub-models of each body group,
			the data layout is a bit different between Nightfire and Half Life.

			Nightfire:
				- Model owns multiple model infos. There is no other useful information in the model element.
				- Model info specifies the skin, and owns multiple meshes.
				- Meshes own triangle mappings and vertices.

			Half Life:
				- mstudiomodel_t owns multiple meshes, and holds info on vertices, normals, and blends.
				- mstudiomesh_t specifies the skin, and owns triangle mappings and normals (apparently unused).

			These can roughly be combined as follows:
				- One mstudiomodel_t should be created for each NF model.
				- One child mstudiomesh_t should be created for each NF model info underneath this model,
				  and should take its skin from that model info.
				- All meshes listed underneath the NF model info should have their triangles accumulated together
				  and recorded in the mstudiomesh_t.
				- All vertices listed in each NF mesh under the NF model info should be accumulated together
				  and recorded in the mstudiomodel_t.
				- All other data required by the mstudiomesh_t should be generated and recorded appropriately.

			We also need to generate the relevant vertex/normal/etc. lists from the Nightfire vertex objects.
		*/
	}
}
