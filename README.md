# Tower Defense

## Introduction
Một project làm game **Tower Defense** cơ bản.
Xem demo tại: https://drive.google.com/file/d/1zuRl14MOLJUDyIsPsUPzBojT1DjKS7H4/view?usp=sharing

## Technologies
Project sử dụng IDE và các thư viện sau:
* Code::blocks 17.12 mingw
* SDL2 image devel 2.0.5 mingw
* SDL2 ttf devel 2.0.15 mingw
* SDL2 mixer devel 2.0.4 mingw
* SDL2 devel 2.0.14 mingw

## Contents
Luật chơi, các tính năng của sản phẩm và thuật toán được sử dụng:

#### Luật chơi
Xây dựng tháp pháo để tiêu diệt quái vật, ngăn chúng đến ngôi nhà ở cuối con đường. Cứ mỗi khoảng thời gian, quái sẽ được sinh ra và di chuyển theo một lộ trình cố định. Người chơi tiêu diệt quái bằng cách dùng vàng nhận được để xây tháp, tháp sẽ tấn công quái gần nó nhất. Quái hoàn thành lộ trình sẽ làm mất máu của nhà. Sống sót sau cuộc tấn công của 50 quái, bạn sẽ thắng, ngược lại, bạn sẽ thua. Điểm được tính dựa trên lượng máu còn lại của nhà và số quái tiêu diệt, ngoài ra xây tháp sẽ làm mất điểm. Có thể xem chi tiết hơn phần luật chơi ở giao diện game.

#### Tính năng và thuật toán:
Duy trì biến *type* nhận giá trị từ 0 đến 3 để xác định giao diện nào sẽ được hiển thị.
##### 1. Menu:
* Khi *type = 0*, hàm *RunTheClient()* sẽ được gọi để hiển thị **Menu**.
* Từ **Menu** có thể chọn tính năng **CHƠI**, xem **LUẬT CHƠI** và xem **BẢNG ĐIỂM**. Khi bấm chọn các nút tương ứng với các tính năng thì sẽ kích hoạt các tính năng đó bằng cách thay đổi giá trị của biến *type* và khi thoát tính năng thì *type* sẽ quay về giá trị 0. Hàm *CheckInside* dùng thuật toán đọc vào sự kiện bấm nút, rồi kiểm tra tọa độ của lần bấm đó nằm trong hình chữ nhật ứng với nút nào để xác định nút được bấm.
##### 2. Luật chơi:
* Khi *type = 2*, hàm *RunTheGuide()* sẽ được gọi để hiển thị **Luật chơi**.
* Có 4 tab hiển thị. 
* Có 2 nút **chuyển trước** và **chuyển sau** ở góc phải dưới để chuyển giữa các tab. Ở tab cuối không có nút **chuyển sau**. Nếu bấm nút **chuyển trước** ở tab đầu thì sẽ quay lại giao diện **Menu**. Hàm *CheckInsideCircle* dùng thuật toán đọc vào sự kiện bấm nút, rồi kiểm tra tọa độ của lần bấm đó nằm trong hình tròn ứng với nút nào để xác định nút được bấm.

##### 3. Bảng điểm:
* Khi *type = 3*, hàm *RunTheScoreBoard()* sẽ được gọi để hiển thị **Bảng điểm**.
* Hiển thị điểm của tối đa 5 lần chơi có điểm cao nhất. Việc này được thực hiện bằng cách duy trì một **multiset** *List_of_score* lưu điểm của các lần chơi. Mỗi khi một lần chơi được hoàn thành, hàm *updateRankingTable* sẽ được gọi để thêm điểm vào **multiset**, nếu vượt quá 5 phần tử thì sẽ xóa phần tử cuối.
* Có một nút **chuyển trước** ở góc phải dưới để trở về giao diện **Menu**. Thuật toán xác định nút bấm tương tự như ở phần **Luật chơi**.

##### 4. Game:
* Khi *type = 1*, hàm *RunTheGame()* sẽ được gọi để tạo một lượt chơi mới.
* Cứ một khoảng thời gian khoảng 110ms (được quy định bằng biến *STEP*), một loạt sự kiện sẽ xảy ra trong game, được gọi là một bước.
Số bước được lưu bằng biến *Time*.
* Giao diện game gồm 2 thành phần chính là **Map** và **Shop**:
    * **Map (Bản đồ)** là một bảng gồm 7*14 ô vuông, mỗi ô vuông thuộc vào một trong các loại *GrassGround, DLGround, DRGround, HGround, ULGround, URGround, VGround, Castle, Rock, Well, House, Grass, Log*. Trong đó, *GrasGround* là loại ô có thể xây dựng tháp trên ô đó, *DLGround, DRGround, HGround, ULGround, URGround, VGround* là các ô nằm trên đường đi của quái, các loại ô còn lại là vật cản và không thể xây tháp trên đó. Cấu trúc của bảng là cố định, được đọc từ file *Map.txt* khi game được khởi tạo.
    * **Shop (Cửa hàng)** nằm phía dưới bản đồ. Trong **Shop** hiển thị số tiền, số điểm, thanh máu nhà chính và tùy vào trạng thái sẽ hiển thị 3 ô mua tháp hoặc ô hủy mua tháp. Thanh máu sẽ được hiển thị dựa trên tỉ lệ giữa số máu hiện tại và số máu tối đa của nhà chính (100). Tùy theo lượng tiền, ô mua tháp sẽ hiển thị bình thường nếu lượng tiền hiện tại >= giá của tháp, ngược lại sẽ hiển thị màu xám (giá của tháp được được ghi trong ô mua tháp). Khi đang chọn mua 1 tháp, 3 ô mua tháp sẽ được thay thế bằng ô thoát mua tháp. Các tính năng trên được thực hiện trong hàm *RenderShop*.
* Các đối tượng trong game:
    * **Enemy (quái)**: Cứ vài bước trong game, quái sẽ được sinh ra, số quái còn lại ít thì quái sẽ sinh ra nhanh. Danh sách quái đang tồn tại được lưu trong **vector** *enemylist*. Quái có chỉ số như máu, tốc độ di chuyển, sát thương,... khác nhau giữa các loại và được quy định trong file *Enemy.cpp*. Lộ trình của quái là cố định và giống nhau, ở mỗi bước, quái sẽ di chuyển dựa trên ô đang đứng (Ví dụ: nếu đang đứng trên ô *HGround*, quái sẽ đi từ đầu đến cuối ô, nếu đang đứng trên ô *DLGround*, quái sẽ đi đến trung tâm ô rồi đổi hướng sang trái,...). Việc di chuyển này được quy định trong hàm *MoveEnemy* bằng thuật toán cập nhật tọa độ của quái dựa trên vận tốc và hướng di chuyển. Quái có máu <=0 sẽ biến mất và được xóa khỏi *enemylist*. Quái đến được nhà chính cũng sẽ được xử lý tương tự, nhưng nó sẽ gây sát thương lên nhà chính trước khi biến mất.
    * **Tower (tháp)**: gồm 3 loại, trong đó có 2 loại có thể tấn công và một loại tăng tiền nhận được. Những tháp đang tồn tại được lưu trong **vector** *towerlist*. Tháp có các chỉ số như thời gian nạp đạn, tầm bắn, thời điểm lần cuối tấn công,... Ở mỗi bước, nếu đã nạp đạn xong, tháp có thể bắn sẽ duyệt qua *enemylist*, tính khoảng cách giữa Euclid giữa nó và quái bằng hàm *getdis*, chọn quái gần nhất trong tầm làm mục tiêu và tạo ra một viên đạn ứng với loại tháp nhắm vào mục tiêu đó. Với tháp tăng tiền, cứ 6 bước tháp sẽ cho thêm tiền. Tháp đã xây không thể gỡ bỏ nhưng có thể thay thế bằng cách xây tháp khác đè lên. Tháp bị thay thế sẽ bị xóa khỏi game và *towerlist*.
    * **Bullet (đạn)**: gồm 2 loại, tương ứng với các loại tháp. Khi tháp tạo ra một viên đạn, viên đạn đó sẽ được thêm vào **vector** *bulletlist*. Đạn có các chỉ số như sát thương, tốc độ bay, mục tiêu... Ở mỗi bước, nếu quái mục tiêu của viên đạn đã bị xóa, nó cũng sẽ biến mất, ngược lại, nó sẽ di chuyển một đoạn trên vector nối giữa nó với mục tiêu (được thực hiện bởi hàm *Move* trong class *Bullet*). Khi viên đạn đến chỗ mục tiêu, nó sẽ gây sát thương cho mục tiêu rồi biến mất, bị xóa khỏi game và *bulletlist*.
    * **Coin (tiền)**: được quy định bởi biến *coin* trong class *Shop*. Khi khởi tạo game, coin = 300. Sau đó, cứ 6 bước sẽ nhận được 1 tiền, cộng thêm 2 tiền với mỗi tháp tăng tiền tồn tại trên bản đồ. Khi xây tháp, tiền sẽ giảm đi 50, 100 hoặc 150 tùy theo loại tháp được xây.
    * **Điểm**: Mỗi máu của nhà chính ứng với 10 điểm, vì vậy khi khởi tạo game sẽ có sẵn 1000 điểm, số điểm này sẽ bị trừ dần khi để địch tấn công nhà chính và xây tháp (xây mỗi tháp mất 10 điểm). Có thể tăng điểm bằng cách tiêu diệt quái. 
* Một số tính năng:
    * **Xây tháp**: Bắt đầu việc xây tháp bằng cách ấn vào biểu tượng mua tháp trong **Shop**, sau đó di chuyển chuột trên **Map**. Trên **Map** sẽ hiển thị vị trí tháp sẽ được xây đồng thời hiển thị có thể xây được hay không (nếu xây được thì hình hiển thị sẽ màu xanh, ngược lại hình sẽ có màu đỏ). Việc này được thực hiện bằng cách đọc những sự kiện di chuyển của trỏ chuột, sau đó dựa theo vị trí của sự kiện để xác định con trỏ chuột đang ở ô nào của bảng và kiểm tra xem đó có phải ô được phép xây tháp không. Ở những vị trí được phép xây, nếu bấm chuột trái sẽ xây dựng tháp tương ứng. 
    * **Hiển thị thắng thua**: Khi đạt điều kiện để thắng hoặc thua, sẽ có hiển thị hình thông báo tương ứng, kết thúc lượt chơi, cập nhật bảng điểm và quay về **Menu**.
    * **Thoát**: Có thể ngay lập tức kết thúc lượt chơi bằng cách bấm nút thoát cửa sổ, khi đó sẽ quay về **Menu** nhưng không cập nhật bảng điểm.




