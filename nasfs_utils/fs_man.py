import bson

class FSMan():

    def __init__(self):
        self._db_name = "meta_db"
        self._super_file = "super_file"

    def _create_meta_db(self):
        return

    def create_fs(self, vol, raidLv):
        file = open(self._super_file, 'bx')
        file.write(bson.dumps({"vol":vol, "raid":raidLv}))
        file.close()

    def add_vol(self, mount, vol):
        return

    def remove_vol(self, mount, vol):
        return

    def balance_fs(self, mount):
        return
