import os
import requests
from PyPDF2 import PdfMerger

chapters_url = {
    "Intro": {
        "Preface": "preface.pdf",
        "Table of Contents": "toc.pdf",
        "Dialogue": "dialogue-threeeasy.pdf",
        "Introduction": "intro.pdf",
    },

    "Virtualization": {
        "Dialogue: Virtualization": "dialogue-virtualization.pdf",
        "Processes": "cpu-intro.pdf",
        "Process API": "cpu-api.pdf",
        "Direct Execution": "cpu-mechanisms.pdf",
        "CPU Scheduling": "cpu-sched.pdf",
        "Multi-level Feedback": "cpu-sched-mlfq.pdf",
        "Lottery Scheduling": "cpu-sched-lottery.pdf",
        "Multi-CPU Scheduling": "cpu-sched-multiple.pdf",
        "Summary: CPU": "cpu-dialogue.pdf",
        "Dialogue: Virtual Memory": "dialogue-vm.pdf",
        "Address Spaces": "vm-intro.pdf",
        "Memory API": "vm-api.pdf",
        "Address Translation": "vm-mechanism.pdf",
        "Segmentation": "vm-segmentation.pdf",
        "Free Space Management": "vm-freespace.pdf",
        "Introduction to Paging": "vm-paging.pdf",
        "Translation Lookaside Buffers": "vm-tlbs.pdf",
        "Advanced Page Tables": "vm-smalltables.pdf",
        "Swapping: Mechanisms": "vm-beyondphys.pdf",
        "Swapping: Policies": "vm-beyondphys-policy.pdf",
        "Complete VM Systems": "vm-complete.pdf",
        "Summary: Virtual Memory": "vm-dialogue.pdf",
    },

    "Concurrency": {
        "Dialogue": "dialogue-concurrency.pdf",
        "Concurrency and Threads": "threads-intro.pdf",
        "Thread API": "threads-api.pdf",
        "Locks": "threads-locks.pdf",
        "Locked Data Structures": "threads-locks-usage.pdf",
        "Condition Variables": "threads-cv.pdf",
        "Semaphores": "threads-sema.pdf",
        "Concurrency Bugs": "threads-bugs.pdf",
        "Event-Based Concurrency": "threads-events.pdf",
        "Summary": "threads-dialogue.pdf",
    },

    "Persistence": {
        "Dialogue: Persistence": "dialogue-persistence.pdf",
        "I/O Devices": "file-devices.pdf",
        "Hard Disk Drives": "file-disks.pdf",
        "Redundant Disk Arrays (RAID)": "file-raid.pdf",
        "Files and Directories": "file-intro.pdf",
        "File System Implementation": "file-implementation.pdf",
        "Fast File System (FFS)": "file-ffs.pdf",
        "FSCK and Journaling": "file-journaling.pdf",
        "Log-structured File System (LFS)": "file-lfs.pdf",
        "Flash-based SSDs": "file-ssd.pdf",
        "Data Integrity and Protection": "file-integrity.pdf",
        "Summary: Files": "file-dialogue.pdf",
        "Dialogue: Distribution": "dialogue-distribution.pdf",
        "Distributed Systems": "dist-intro.pdf",
        "Network File System (NFS)": "dist-nfs.pdf",
        "Andrew File System (AFS)": "dist-afs.pdf",
        "Summary: Distribution": "dist-dialogue.pdf",
    },

    "Security": {
        "Dialogue": "dialogue-security.pdf",
        "Intro Security": "security-intro.pdf",
        "Authentication": "security-authentication.pdf",
        "Access Control": "security-access.pdf",
        "Cryptography": "security-crypto.pdf",
        "Distributed": "security-distributed.pdf",
    },

    "Appendices": {
        "Dialogue: Virtual Machine Monitor",
        "Virtual Machines": "vmm-intro.pdf",
        "Dialogue: Monitors": "dialogue-monitors.pdf",
        "Monitors": "threads-monitors.pdf",
        "Dialogue: Labs": "dialogue-labs.pdf",
        "Lab Tutorial": "lab-tutorial.pdf",
        "Systems Labs": "lab-projects-systems.pdf",
        "xv6 Labs": "lab-projects-xv6.pdf",
    },
}
output_dir = "ostep_chapters"
output_pdf = "OSTEP_Complete.pdf"
web_url_root = "https://pages.cs.wisc.edu/~remzi/OSTEP/"

def download_chapters():
    os.makedirs(output_dir, exist_ok=True)
    for section in chapter_urls:
        print(f"Downloading section {section}...")
        section_name = os.path.join(output_dir, section)
        if not os.path.exists(section_name):
            print(f"Creating new directory in {output_dir}: {section}")
            os.makedirs(section_name)
        for chapter_name, chapter_url in chapter_urls[section].items():
            filename = os.path.join(section_name, chapter_name)
            if not os.path.exists(filename):
                url = web_url_root + chapter_url
                print(f"Downloading {url}...")
                response = requests.get(url)
                with open(filename, 'wb') as f:
                    f.write(response.content)
            else:
                print(f"{filename} already exists, skipping.")

def merge_pdfs():
    merger = PdfMerger()
    for url in chapter_urls:
        chapter_file = os.path.join(output_dir, os.path.basename(url))
        print(f"Adding {chapter_file} to the merged PDF...")
        merger.append(chapter_file)
    merger.write(output_pdf)
    merger.close()
    print(f"All chapters merged into {output_pdf}.")

if __name__ == "__main__":
    download_chapters()
    merge_pdfs()