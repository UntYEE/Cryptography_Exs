#coding=utf-8
def find_repeating_substrings(input_string):
    substring_count = {}
    repeating_substrings = []

    for i in range(len(input_string) - 2):
        for j in range(i + 3, len(input_string) + 1):
            substring = input_string[i:j]
            if substring in substring_count:
                substring_count[substring] += 1
            else:
                substring_count[substring] = 1

    for substring, count in substring_count.items():
        if count >= 2:
            repeating_substrings.append((substring, count))

    # 找出出现次数最多的子串
    max_count = max(repeating_substrings, key=lambda x: x[1])[1]
    most_frequent_substrings = [s[0] for s in repeating_substrings if s[1] == max_count]

    print(max_count)
    return most_frequent_substrings

input_str = "LSIANACHMLATOIHNTADHMOAIOAXIGIAMZOAGOSOXAAdHIEAMAANOVTOAASEOSHIIHNTAPHODOXAOILIXTEEMVAOVACCMNOVOAAOXMANOZSAVEXMHLLOHSETODACETAXTAAIMOTATZASIAAAHZIIWXSANNPALXHVLHASVISAVHALLSMOMSTHASOXZAOOZODOASASTHLOHVIALHACOXASWONIGMNPVAPHHOOONOALHAHOXAAAOOALAAMGTLGXVZIXHOMVNAMOOOVHOXODLTDOAEWHIOXCANDAXITIDALGAAAENXADANIAANIAVAIOHAANDAXADOX"
most_frequent_substrings = find_repeating_substrings(input_str)
print( most_frequent_substrings)


# 示例用法
#input_str = "LSIANACHMLATOIHNTADHMOAIOAXIGIAMZOAGOSOXAAdHIEAMAANOVTOAASEOSHIIHNTAPHODOXAOILIXTEEMVAOVACCMNOVOAAOXMANOZSAVEXMHLLOHSETODACETAXTAAIMOTATZASIAAAHZIIWXSANNPALXHVLHASVISAVHALLSMOMSTHASOXZAOOZODOASASTHLOHVIALHACOXASWONIGMNPVAPHHOOONOALHAHOXAAAOOALAAMGTLGXVZIXHOMVNAMOOOVHOXODLTDOAEWHIOXCANDAXITIDALGAAAENXADANIAANIAVAIOHAANDAXADOX"


