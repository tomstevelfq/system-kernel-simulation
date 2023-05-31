class FIFO:
    def __init__(self, frame_count):
        self.frame_count = frame_count  # 物理内存的帧数
        self.frames = []  # 物理内存的帧列表
        self.page_queue = []  # 页面队列

    def is_page_fault(self, page):
        return page not in self.frames

    def handle_page_fault(self, page):
        if len(self.frames) < self.frame_count:
            self.frames.append(page)
        else:
            removed_page = self.page_queue.pop(0)
            self.frames.remove(removed_page)
            self.frames.append(page)

        self.page_queue.append(page)

    def print_frames(self):
        print("物理内存帧内容：", self.frames)


# 示例使用
fifo = FIFO(4)  # 创建FIFO对象，物理内存帧数为4

# 页面引用序列
page_sequence = [2, 3, 1, 4, 3, 2, 1, 5, 2, 4]

for page in page_sequence:
    if fifo.is_page_fault(page):
        print("页面缺失：", page)
        fifo.handle_page_fault(page)
        fifo.print_frames()

