# -
c/c++，python的各种管理系统
import tkinter as tk
from tkinter import ttk
import csv
from typing import List
from tkinter import filedialog
tk.Tk().withdraw()  # or root = tk.Tk(); root.withdraw()
class Contact:
    def __init__(self, name: str, company: str, phone: str, email: str, instant_msg: str):
        self.name = name
        self.company = company
        self.phone = phone
        self.email = email
        self.instant_msg = instant_msg

    def to_list(self) -> List[str]:
        return [self.name, self.company, self.phone, self.email, self.instant_msg]


class AddressBook:
    def __init__(self):
        self.contacts = []

    def add_contact(self, contact: Contact):
        self.contacts.append(contact)

    def remove_contact(self, idx: int):
        del self.contacts[idx]

    def edit_contact(self, idx: int, contact: Contact):
        self.contacts[idx] = contact

    def get_contacts(self) -> List[Contact]:
        return self.contacts

    def search_contacts(self, keyword: str) -> List[Contact]:
        return [c for c in self.contacts if keyword in c.name or keyword in c.company]


class AddressBookUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("通讯录管理系统")
        self.search_entry = tk.Entry(self.root)
        self.listbox = tk.Listbox(self.root)
        self.search_btn = tk.Button(self.root, text="搜索", command=self.search_contacts)

        # 创建通讯录对象
        self.addressbook = AddressBook()

        # 创建界面组件
        self.create_menu_bar()
        self.create_contact_info_section()
        self.create_contact_list_section()
        self.create_status_bar()

    def run(self):
        self.root.mainloop()

    def create_menu_bar(self):
        menu_bar = tk.Menu(self.root)

        file_menu = tk.Menu(menu_bar, tearoff=0)
        file_menu.add_command(label="导入", command=self.import_contacts)
        file_menu.add_command(label="导出", command=self.export_contacts)
        file_menu.add_separator()
        file_menu.add_command(label="退出", command=self.root.quit)
        menu_bar.add_cascade(label="文件", menu=file_menu)

        self.root.config(menu=menu_bar)

    def create_contact_info_section(self):
        info_frame = ttk.LabelFrame(self.root, text="联系人详情")
        info_frame.grid(row=0, column=0, padx=10, pady=10, sticky="NSEW")

        # 姓名
        ttk.Label(info_frame, text="姓名：").grid(row=0, column=0, pady=5)
        self.name_entry = ttk.Entry(info_frame)
        self.name_entry.grid(row=0, column=1, pady=5)

        # 公司
        ttk.Label(info_frame, text="公司：").grid(row=1, column=0, pady=5)
        self.company_entry = ttk.Entry(info_frame)
        self.company_entry.grid(row=1, column=1, pady=5)

        # 电话
        ttk.Label(info_frame, text="电话：").grid(row=2, column=0, pady=5)
        self.phone_entry = ttk.Entry(info_frame)
        self.phone_entry.grid(row=2, column=1, pady=5)

        # 邮箱
        ttk.Label(info_frame, text="邮箱：").grid(row=3, column=0, pady=5)
        self.email_entry = ttk.Entry(info_frame)
        self.email_entry.grid(row=3, column=1, pady=5)

        # 即时通讯
        ttk.Label(info_frame, text="即时通讯：").grid(row=4, column=0, pady=5)
        self.instant_msg_entry = ttk.Entry(info_frame)
        self.instant_msg_entry.grid(row=4, column=1, pady=5)
        #搜索
        ttk.Label(info_frame, text="搜索：").grid(row=5, column=0, pady=5)
        self.search_entry = ttk.Entry(info_frame)
        self.search_entry.grid(row=5, column=1, pady=5)

        self.search_btn = ttk.Button(info_frame, text="搜索", command=self.search_contacts)
        self.search_btn.grid(row=5, column=2, pady=5)
        # 操作按钮
        button_frame = ttk.Frame(info_frame)
        button_frame.grid(row=5, columnspan=2, pady=10)

        ttk.Button(button_frame, text="添加", command=self.add_contact).grid(row=0, column=0, padx=5)
        ttk.Button(button_frame, text="编辑", command=self.edit_contact).grid(row=0, column=1, padx=5)
        ttk.Button(button_frame, text="删除", command=self.delete_contact).grid(row=0, column=2, padx=5)
        ttk.Button(button_frame, text="清空", command=self.clear_contact_info).grid(row=0, column=3, padx=5)

    def create_contact_list_section(self):
        list_frame = ttk.LabelFrame(self.root, text="联系人列表")
        list_frame.grid(row=0, column=1, padx=10, pady=10, sticky="NSEW")

        # 列表框
        self.listbox = tk.Listbox(list_frame)
        self.listbox.pack(expand=True, fill="both")

        # 滚动条
        scrollbar = tk.Scrollbar(list_frame)
        scrollbar.pack(side="right", fill="y")

        # 绑定滚动条和列表框
        self.listbox.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.listbox.yview)

        # 绑定鼠标左键双击事件
        self.listbox.bind("<Double-Button-1>", self.on_contact_selected)

    def create_status_bar(self):
        self.status_bar = ttk.Label(self.root, text="就绪", anchor="w")
        self.status_bar.grid(row=1, column=0, columnspan=2, sticky="WE")

    def update_status_bar(self, message: str):
        self.status_bar.config(text=message)

    def import_contacts(self):
        filename = tk.filedialog.askopenfilename(title="选择文件", filetypes=[("CSV 文件", "*.csv")])
        try:
            with open(filename, "r", encoding="utf-8") as f:
                reader = csv.reader(f)
                for row in reader:
                    if len(row) == 0:
                        continue
                    contact = Contact(*row)
                    self.addressbook.add_contact(contact)
            self.refresh_contact_list()
            self.update_status_bar("导入成功")
        except Exception as e:
            self.update_status_bar(f"导入失败：{e.args}")

    def export_contacts(self):
        if len(self.addressbook.get_contacts()) == 0:
            self.update_status_bar("通讯录为空，无法导出")
            return
        filename = tk.filedialog.asksaveasfilename(title="保存文件", defaultextension=".csv",
                                                   filetypes=[("CSV 文件", "*.csv")])
        try:
            with open(filename, "w", encoding="utf-8", newline="") as f:
                writer = csv.writer(f)
                for contact in self.addressbook.get_contacts():
                    writer.writerow(contact.to_list())
            self.update_status_bar("导出成功")
        except Exception as e:
            self.update_status_bar(f"导出失败：{e.args}")

    def add_contact(self):
        name = self.name_entry.get()
        company = self.company_entry.get()
        phone = self.phone_entry.get()
        email = self.email_entry.get()
        instant_msg = self.instant_msg_entry.get()
        if name == "":
            self.update_status_bar("姓名不能为空")
            return
        contact = Contact(name, company, phone, email, instant_msg)
        self.addressbook.add_contact(contact)
        self.clear_contact_info()
        self.refresh_contact_list()
        self.update_status_bar("添加成功")

    def edit_contact(self):
        idx = self.get_selected_contact_idx()
        if idx is None:
            self.update_status_bar("请选择要编辑的联系人")
            return
        name = self.name_entry.get()
        company = self.company_entry.get()
        phone = self.phone_entry.get()
        email = self.email_entry.get()
        instant_msg = self.instant_msg_entry.get()
        if name == "":
            self.update_status_bar("姓名不能为空")
            return
        contact = Contact(name, company, phone, email, instant_msg)
        self.addressbook.edit_contact(idx, contact)
        self.clear_contact_info()
        self.refresh_contact_list()
        self.update_status_bar("编辑成功")

    def delete_contact(self):
        idx = self.get_selected_contact_idx()
        if idx is None:
            self.update_status_bar("请选择要删除的联系人")
            return
        self.addressbook.remove_contact(idx)
        self.clear_contact_info()
        self.refresh_contact_list()
        self.update_status_bar("删除成功")

    def clear_contact_info(self):
        self.name_entry.delete(0, tk.END)
        self.company_entry.delete(0, tk.END)
        self.phone_entry.delete(0, tk.END)
        self.email_entry.delete(0, tk.END)
        self.instant_msg_entry.delete(0, tk.END)

    def get_selected_contact_idx(self):
        selection = self.listbox.curselection()
        if len(selection) == 0:
            return None
        else:
            return selection[0]

    def refresh_contact_list(self):
        self.listbox.delete(0, tk.END)
        for contact in self.addressbook.get_contacts():
            self.listbox.insert(tk.END, contact.name)

    def search_contacts(self):
        keyword = self.search_entry.get()
        name = self.name_entry.get()
        if len(keyword) == 0:
            self.update_status_bar("请输入关键词")
        results = self.addressbook.search_contacts(keyword)
        if len(results) == 0:
            self.update_status_bar("未找到匹配项")
            return
        self.listbox.delete(0, tk.END)
        for contact in results:
            self.listbox.insert(tk.END, contact.name)
        self.update_status_bar(f"共找到 {len(results)} 个匹配项")


    def on_contact_selected(self, event):
        idx = self.get_selected_contact_idx()
        if idx is None:
            return
        contact = self.addressbook.contacts[idx]
        self.name_entry.delete(0, tk.END)
        self.name_entry.insert(0, contact.name)
        self.company_entry.delete(0, tk.END)
        self.company_entry.insert(0, contact.company)
        self.phone_entry.delete(0, tk.END)
        self.phone_entry.insert(0, contact.phone)
        self.email_entry.delete(0, tk.END)
        self.email_entry.insert(0, contact.email)
        self.instant_msg_entry.delete(0, tk.END)
        self.instant_msg_entry.insert(0, contact.instant_msg)

# 创建通讯录管理程序对象并运行
ab_ui = AddressBookUI()
ab_ui.run()
